#pragma once
#include "gns/irreducible_polynomial.h"
#include "gns/laurent_series.h"
#include "gns/matrix.h"
#include "gns/matrix_operator.h"
#include "gns/vector.h"
#include "gns/util.h"
#include <memory>
#include <utility>
#include <vector>

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
GaloisFieldPolynomial<Base>
GetSobolGeneratorPolynomial(const size_t dim, const size_t i, const size_t k)
{
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
Matrix<Base>
MakeSobolGeneratorMatrix(
    const size_t dim,
    const std::vector<GaloisFieldPolynomial<Base>>& irreducibles,
    const size_t max_bit)
{
  assert(dim > 0);
  std::unique_ptr<GaloisField<Base>[]> data(
      new GaloisField<Base>[max_bit * max_bit]);
  // for each row
  const size_t degree = irreducibles[dim - 1].degree();
  GaloisFieldPolynomial<2> denominator = irreducibles[dim - 1];
  for (size_t row = 0; row < max_bit; ++row) {
    const size_t q = row / degree;
    const size_t k = row % degree;
    GaloisFieldPolynomial<Base> numerator
      = GetSobolGeneratorPolynomial<Base>(dim, q, k);
    std::unique_ptr<GaloisField<Base>[]> laurent_series
      = SolveLaurentSeriesDivision(numerator, denominator, max_bit + 1);
    for (size_t col = 0; col < max_bit; ++col) {
      data[row * max_bit + col] = laurent_series[col + 1];
    }
    denominator *= irreducibles[dim - 1];
  }
  return Matrix<Base>(max_bit, max_bit, std::move(data));
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
  Sobol(
      const size_t dimension, const size_t seed = 0, const size_t max_bit = 32)
    : dimension_(dimension),
    seed_(seed),
    max_bit_(max_bit),
    generator_matrix_(0) {
      assert(dimension_ > 0);
      IrreduciblePolynomialGenerator<Base> generator;
      std::vector<GaloisFieldPolynomial<Base>> irreducibles 
        = generator(dimension_);
      for (size_t dim = 0; dim < dimension_; ++dim) {
        Matrix<Base>&& matrix
          = MakeSobolGeneratorMatrix<Base>(dim + 1, irreducibles, max_bit_);
        generator_matrix_.push_back(std::move(matrix));
      }
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
    std::pair<size_t, std::unique_ptr<GaloisField<Base>[]>> data
      = CalculateBaseAdic<Base>(seed_);
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

}  // namespace gns
