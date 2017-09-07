#pragma once
#include <memory>
#include <utility>
#include <vector>
#include "gns/irreducible_polynomial.h"
#include "gns/laurent_series.h"
#include "gns/matrix.h"
#include "gns/matrix_operator.h"
#include "gns/util.h"
#include "gns/vector.h"

namespace gns {
/**
 * @brief
 *
 *
 * @tparam Base
 * @param dim dimension of generator polynomial. 1 to maximum dimension.
 * @param i
 * @param k
 *
 * @return
 */
template <int Base>
GaloisFieldPolynomial<Base> GetSobolGeneratorPolynomial(const size_t dim,
                                                        const size_t i,
                                                        const size_t k) {
  assert(dim > 0);
  // k is degree
  std::unique_ptr<GaloisField<Base>[]> data(new GaloisField<Base>[k + 1]);
  data[k] = 1;
  return GaloisFieldPolynomial<Base>(k, std::move(data));
}
/**
 * @brief
 *
 * @tparam Base
 * @param dim dimension of generator matrix. 1 to maximum dimension.
 * @param irreducibles
 * @param max_bit
 *
 * @return
 */
template <int Base>
Matrix<Base> MakeSobolGeneratorMatrix(
    const size_t dim,
    const std::vector<GaloisFieldPolynomial<Base>>& irreducibles,
    const size_t max_bit) {
  assert(dim > 0);
  std::unique_ptr<GaloisField<Base>[]> data(
      new GaloisField<Base>[max_bit * max_bit]);
  const size_t degree = irreducibles[dim - 1].degree();

  // calcualte denominators in advance
  std::vector<GaloisFieldPolynomial<Base>> denominator;
  GaloisFieldPolynomial<Base> irreducible = irreducibles[dim - 1];
  const size_t max_quotient = static_cast<size_t>(max_bit / degree);
  for (size_t q = 0; q <= max_quotient; ++q) {
    denominator.push_back(irreducible);
    irreducible *= irreducibles[dim - 1];
  }

  // for each row
  for (size_t row = 0; row < max_bit; ++row) {
    const size_t q = row / degree;
    const size_t k = row % degree;

    GaloisFieldPolynomial<Base> numerator =
        GetSobolGeneratorPolynomial<Base>(dim, q, k);
    std::unique_ptr<GaloisField<Base>[]> laurent_series =
        SolveLaurentSeriesDivision(numerator, denominator[q], max_bit + 1);
    for (size_t col = 0; col < max_bit; ++col) {
      data[row * max_bit + col] = laurent_series[col + 1];
    }
  }
  return Matrix<Base>(max_bit, max_bit, std::move(data));
}
/**
 * @brief 
 *
 * @tparam Base
 *
 * @return 
 */
template<int Base>
std::vector<Matrix<Base>>
MakeSobolGeneratorMatrices(const size_t dimension, const size_t max_bit)
{
  std::vector<Matrix<Base>> generator_matrix(0);
  IrreduciblePolynomialGenerator<Base> generator;
  std::vector<GaloisFieldPolynomial<Base>> irreducibles =
      generator(dimension);
  for (size_t dim = 0; dim < dimension; ++dim) {
    Matrix<Base>&& matrix =
        MakeSobolGeneratorMatrix<Base>(dim + 1, irreducibles, max_bit);
    generator_matrix.push_back(std::move(matrix));
  }
  return generator_matrix;
}
/**
 * @brief
 *
 * @tparam Base
 */
template <int Base>
class Sobol {
  // private typedef
 private:
  // public typedef
 public:
  // public function
 public:
  Sobol(const size_t dimension, const size_t seed = 0,
        const size_t max_bit = 32)
      : dimension_(dimension),
        seed_(seed),
        max_bit_(max_bit),
        generator_matrix_(0) {
    assert(dimension_ > 0);
    generator_matrix_ = MakeSobolGeneratorMatrices<Base>(dimension_, max_bit_);
  }

  std::unique_ptr<double[]> Next() {
    std::unique_ptr<double[]> result(new double[dimension_]);
    // if seed_ is zero, point is zero.
    if (seed_ == 0) {
      ++seed_;
      std::fill(result.get(), result.get() + dimension_, 0);
      return result;
    }
    // calc base adic expansion of seed_
    std::pair<size_t, std::unique_ptr<GaloisField<Base>[]>> data =
        CalculateBaseAdic<Base>(seed_);
    Vector<Base> n(data.first, std::move(data.second));

    // get generator matrix
    for (size_t dim = 0; dim < dimension_; ++dim) {
      // multiply generator matrix
      const Vector<Base>& vec = generator_matrix_[dim] * n;
      result[dim] = BaseAdicToDouble(vec);
    }

    // update seed
    ++seed_;
    return result;
  }
  // private function
 private:
  // private members
 private:
  size_t dimension_;
  size_t seed_;
  size_t max_bit_;
  std::vector<Matrix<Base>> generator_matrix_;
};

/**
 * @brief
 *
 * @tparam Base
 */
template <int Base>
class SobolGrayMap {
  // private typedef
 private:
  // public typedef
 public:
  // public function
 public:
  SobolGrayMap(const size_t dimension, const size_t seed = 0,
        const size_t max_bit = 32)
      : dimension_(dimension),
        seed_(seed),
        max_bit_(max_bit),
        cache_(new double[dimension]),
        points_(0),
        generator_matrix_(0) {
    assert(dimension_ > 0);
    // for storing
    for (size_t dim = 0; dim < dimension_; ++dim) {
      points_.push_back(Vector<Base>(max_bit_));
      std::fill(points_[dim].begin(), points_[dim].end(), 0);
    }
    generator_matrix_ = MakeSobolGeneratorMatrices<Base>(dimension_, max_bit_);
  }

  const std::unique_ptr<double[]>& Next() {
    // if seed_ is zero, point is zero.
    if (seed_ == 0) {
      ++seed_;
      std::fill(cache_.get(), cache_.get() + dimension_, 0);
      return cache_;
    }

    // get generator matrix
    for (size_t dim = 0; dim < dimension_; ++dim) {
      size_t l = 0;
      const GaloisField<Base> coeff = FindCoefficient(seed_, l);
      for (size_t row = 0; row < max_bit_; ++row) {
        points_[dim][row] = (points_[dim][row]
                             + coeff * generator_matrix_[dim](row, l));
      }
      cache_[dim] = BaseAdicToDouble(points_[dim]);
    }

    // update seed
    ++seed_;
    return cache_;
  }
  /**
    @brief 
    $b$ is Base and $b = p^{n}$.
    $$n = \sum_{i=0}^{k} a_{i}b^{i}, a_{i} \in \{0, \ldots, b-1\}$$,
    $$l(n) := \min\{i \mid a_{i} \neq b - 1\}$$
    $$ a = \sum_{i=0}^{k} d_{i}p^{i}$$, $$d_{i} \in \{0, \ldots, p-1}\}$$, $$k < n$$,
    $$ \alpha(a) := \min\{i \mid d_{i} \neq p - 1\}$$,
    then  coefficient $c$ is given by

    $$
      c
      =
      \sum_{i=0}^{\alpha(a_{l(n)} - a_{l(n)+1})}
          x^{i}
    $$

    @param n
    @param l $l(n)$

    @return 
   */
  GaloisField<Base>
  FindCoefficient(const size_t num, size_t& l) const
  {
    assert(num > 0);
    constexpr size_t mask = Base - 1;
    size_t n = num;
    // l(n)
    size_t a0 = 0;
    size_t a1 = 0;
    const size_t num_loop = (std::log2(num) / std::log2(Base)) + 1;
    for (l = 0; l < num_loop; ++l) {
      a0 = n & mask;
      // a(l) == b - 1
      if (a0 != 0) {
        a1 =  BitRightShift<Base>(n) & mask;
        break;
      }
      n = BitRightShift<Base>(n);
    }

    // a = a_{l(n)} - a_{l(n)+1}
    int a = a0 - a1;
    if (a < 0) {
      a += Base;
    }
    const size_t carry_bit = FindCarryBit<Base>(a);
    return GaloisField<Base>(carry_bit);
  }

  // private function
 private:
  // private members
 private:
  size_t dimension_;
  size_t seed_;
  size_t max_bit_;
  std::unique_ptr<double[]> cache_;
  std::vector<Vector<Base>> points_;
  std::vector<Matrix<Base>> generator_matrix_;
};
}  // namespace gns
