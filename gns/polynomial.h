#pragma once
#include "gns/galois_field.h"
#include "gns/galois_field_operator.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>

namespace gns {
template <int Base>
class GaloisFieldPolynomial {
//private typedef
private:
//public typedef
public:
  typedef GaloisField<Base> value_type;
  typedef GaloisField<Base>* iterator;
  typedef const GaloisField<Base>* const_iterator;
//public function
public:
  /**
   * @brief 
   */
  inline
  explicit GaloisFieldPolynomial()
  : coeffs_(new GaloisField<Base>[1])
  {
  }
  /**
   * @brief 
   *
   * @param other
   */
  inline
  GaloisFieldPolynomial(const GaloisFieldPolynomial<Base>& other)
  : coeffs_(new GaloisField<Base>[other.degree_ + 1]),
    degree_(other.degree_)
  {
    std::copy(other.cbegin(), other.cend(), this->begin());
  }
  /**
   * @brief 
   *
   * @param degree
   */
  inline
  GaloisFieldPolynomial(size_t degree)
  : coeffs_(new GaloisField<Base>[degree + 1]),
    degree_(degree)
  {
  }
  /**
   * @brief 
   *
   * @param coeffs
   */
  inline
  GaloisFieldPolynomial(std::initializer_list<unsigned char> coeffs)
  : GaloisFieldPolynomial(coeffs.size() - 1)
  {
    std::copy(coeffs.begin(), coeffs.end(), coeffs_.get());
  }
  /**
   * @brief 
   *
   * @param coeffs
   */
  inline
  GaloisFieldPolynomial(
      const size_t degree, std::unique_ptr<value_type[]> data)
  : coeffs_(std::move(data)),
    degree_(degree)
  {
  }

  inline
  ~GaloisFieldPolynomial()
  {
  }

  inline
  bool operator==(const GaloisFieldPolynomial<Base>& other)
  {
    return degree_ == other.degree_
      && std::equal(other.cbegin(), other.cend(), this->cbegin());
  }

  inline
  bool operator==(const GaloisFieldPolynomial<Base>& other) const
  {
    return const_cast<GaloisFieldPolynomial&>(*this) == other;
  }

  inline
  GaloisFieldPolynomial& operator =(const GaloisFieldPolynomial<Base>& other)
  {
    //self assignment
    if (&other == this) {
      return *this;
    }
    coeffs_ = new GaloisField<Base>[other.degree_ + 1];
    std::copy(other.cbegin(), other.cend(), this->begin());
    return *this;
  }

  inline
  GaloisFieldPolynomial& operator =(GaloisFieldPolynomial<Base>&& other)
  {
    //self assignment never happens?
    degree_ = other.degree_;
    coeffs_ = std::move(other.coeffs_);
    other.coeffs_ = nullptr;
    return *this;
  }

  inline
  GaloisFieldPolynomial& operator+=(const GaloisFieldPolynomial<Base>& other)
  {
    const size_t other_degree = other.degree();

    size_t degree = 0;
    if (degree_ <= other_degree) {
      const size_t min_degree = degree_;
      degree = other_degree;
      std::unique_ptr<value_type []> temp(new value_type[degree + 1]);

      // 0 to minDegree
      for (size_t i = 0; i < min_degree + 1; ++i) {
        temp[i] = coeffs_[i] + other[i];
      }
      // minDegree + 1 to maxDegree
      for (size_t i = min_degree + 1; i < degree + 1; ++i) {
        temp[i] = other[i];
      }
      this->replace_coeffs(std::move(temp), degree);
    } else {
      const size_t min_degree = other_degree;
      degree = degree_;
      std::unique_ptr<value_type []> temp(new value_type[degree + 1]);

      // 0 to min_degree
      for (size_t i = 0; i < min_degree + 1; ++i) {
        temp[i] = coeffs_[i] + other[i];
      }
      // min_degree + 1 to max_degree
      for (size_t i = min_degree + 1; i < degree + 1; ++i) {
        temp[i] = coeffs_[i];
      }
      this->replace_coeffs(std::move(temp), degree);
    }

    return *this;
  }

  GaloisFieldPolynomial& operator-=(const GaloisFieldPolynomial<Base>& other)
  {
    const size_t other_degree = other.degree();

    size_t degree = 0;
    if (degree_ <= other_degree) {
      const size_t min_degree = degree_;
      degree = other_degree;
      std::unique_ptr<GaloisField<Base> []> temp(
          new GaloisField<Base>[degree + 1]);

      // 0 to min_degree
      for (size_t i = 0; i < min_degree + 1; ++i) {
        temp[i] = coeffs_[i] - other[i];
      }
      // min_degree + 1 to max_degree
      for (size_t i = min_degree + 1; i < degree + 1; ++i) {
        temp[i] = -other[i];
      }
      this->replace_coeffs(temp, degree);
    } else {
      const size_t min_degree = other_degree;
      degree = degree_;
      std::unique_ptr<GaloisField<Base>[]> temp(
          new GaloisField<Base>[degree + 1]);

      for (size_t i = 0; i < min_degree + 1; ++i) {
        temp[i] = coeffs_[i] - other[i];
      }
      for (size_t i = min_degree + 1; i < degree + 1; ++i) {
        temp[i] = coeffs_[i];
      }
      this->replace_coeffs(temp, degree);
    }

    return *this;
  }

  GaloisFieldPolynomial& operator*=(const unsigned int multiplier)
  {
    if (multiplier != 0) {
      const GaloisField<Base> mult(multiplier);
      for (size_t i = 0; i < degree_ + 1; ++i) {
        coeffs_[i] = mult * coeffs_[i];
      }
    } else {
      std::unique_ptr<GaloisField<Base> []> temp(new GaloisField<Base> [1]);
      this->replace_coeffs(temp, 0);
    }
    return *this;
  }

  GaloisFieldPolynomial& operator*=(const GaloisFieldPolynomial<Base>& other)
  {
    if (other.IsZero() == true) {
      std::unique_ptr<GaloisField<Base> []> temp(new GaloisField<Base>[1]);
      this->replace_coeffs(temp, 0);
    } else {
      const size_t other_degree = other.degree();
      std::unique_ptr<value_type[]> temp(
          new value_type[degree_ + other_degree + 1]);
      std::fill(temp.get(), temp.get() + degree_ + other_degree + 1, 0);
      for (size_t i = 0; i < degree_ + 1; ++i) {
        for (size_t j = 0; j < other_degree + 1; ++j) {
          temp[i + j] = temp[i + j] + coeffs_[i] * other[j];
        }
      }
      coeffs_.swap(temp);
      degree_ += other_degree;
    }
    return *this;
  }

  inline bool IsZero() const
  {
    const bool is_zero = std::all_of(
        this->cbegin(),
        this->cend(),
        [](const GaloisField<Base>& x){ return x == 0; });
    return is_zero;
  }

  inline
  GaloisField<Base>&
  operator[](const size_t index)
  {
    return coeffs_[index];
  }

  inline
  const GaloisField<Base>&
  operator[](const size_t index) const
  {
    return coeffs_[index];
  }

  inline
  size_t degree()
  {
    return degree_;
  }

  inline
  size_t degree() const
  {
    return degree_;
  }

  inline iterator begin()
  {
    return coeffs_.get();
  }

  inline const_iterator begin() const
  {
    return coeffs_.get();
  }

  inline const_iterator cbegin() const
  {
    return coeffs_.get();
  }

  inline iterator end()
  {
    return coeffs_.get() + degree_ + 1;
  }

  inline const_iterator end() const
  {
    return coeffs_.get() + degree_ + 1;
  }

  inline const_iterator cend() const
  {
    return coeffs_.get() + degree_ + 1;
  }

//private function
private:
  inline
  void replace_coeffs(
      const std::unique_ptr<value_type[]>& coeffs,
      size_t degree)
  {
    // resize requires degree_ has current size of coeffs_
    // shrink degree
    while (coeffs[degree] == 0 && degree > 0) {
      --degree;
    }
    std::unique_ptr<value_type[]> temp(new value_type[degree + 1]);
    std::copy(coeffs.get(), coeffs.get() + degree + 1, temp.get());

    degree_ = degree;
    coeffs_.swap(temp);
  }

//private members
private:
  std::unique_ptr<value_type[]> coeffs_;
  size_t degree_;
};

/**
 * @brief 
 *
 * @tparam Base
 * @param os
 * @param x
 *
 * @return 
 */
template<int Base>
std::ostream&
operator<<(std::ostream& os, const GaloisFieldPolynomial<Base>& x)
{
  std::string data = std::to_string(x[0].value());
  for (size_t i = 1; i < x.degree() + 1; ++i) {
    data = std::to_string(x[i].value())
      + "X^{" 
      + std::to_string(i)
      + "} + " 
      + data;
  }
  os << data;
  return os;
}

/*--------------------------------------------------------------------------
 * free functions
 *------------------------------------------------------------------------*/
/**
 * @brief 
 *
 * @tparam Base
 * @param degree
 * @param coeff
 *
 * @return 
 */
template <int Base>
GaloisFieldPolynomial<Base> MakeBasePolynomial(
    const size_t degree, const GaloisField<Base>& coeff)
{
  GaloisFieldPolynomial<Base> polynomial(degree);
  polynomial[degree] = coeff;
  return std::move(polynomial);
}

/**
 * @brief 
 *
 * @tparam Base
 * @param dividend
 * @param divisor
 * dividend = quotient * divisor + residual
 *
 * @return 
 */
template <int Base>
std::pair<GaloisFieldPolynomial<Base>, GaloisFieldPolynomial<Base>>
EuclideanDivision(
    const GaloisFieldPolynomial<Base>& dividend,
    const GaloisFieldPolynomial<Base>& divisor)
{
  GaloisFieldPolynomial<Base> residual(dividend);
  const size_t divisor_degree = divisor.degree();
  GaloisFieldPolynomial<Base> quotient(residual.degree() - divisor_degree);

  while (residual.degree() >= divisor_degree) {
    const size_t degree = residual.degree() - divisor_degree;
    const GaloisField<Base> residual_coeff = residual[residual.degree()];
    const GaloisField<Base> divisor_coeff = divisor[divisor_degree];
    const GaloisField<Base> coeff = residual_coeff / divisor_coeff;
    GaloisFieldPolynomial<Base> temp = MakeBasePolynomial<Base>(degree, coeff);
    quotient += temp;

    temp *= divisor;
    // residual -= mult * divisor
    residual -= temp;
    if(residual.IsZero()) {
      break;
    }
  }
  // quaotient, residual
  return std::make_pair(quotient, residual);
}

template <int Base>
std::unique_ptr<GaloisField<Base>[]>
SolveLaurentSeriesDivision(
    const GaloisFieldPolynomial<Base>& a,
    const GaloisFieldPolynomial<Base>& b,
    const size_t max_degree)
{
  const size_t n = a.degree();
  const size_t m = b.degree();
  assert(n < m);
  std::unique_ptr<GaloisField<Base>[]> c(new GaloisField<Base>[max_degree + 1]);
  // calculate c = a / b
  // assuming m := deg(a) < deg(b) =: n

  // first part equations
  for (size_t i = 0; i < -(-m + n + 1); ++i) {
    c[i] = 0;
  }
  // second part equations
  for (int k = n; k >= 0; --k) {
    GaloisField<Base> sum(0);
    for (size_t j = 1; j <= n - k; ++j) {
      sum = sum + b[m - j] * c[-(-m + k + j)];
    }
    c[-(-m + k)] = (a[k] - sum) / b[m];
  }
  // third part equations
  for (size_t i = 1; i < max_degree - m + 1; ++i) {
    // sum
    GaloisField<Base> sum(0);
    for (size_t j = 0; j < m; ++j) {
      sum = sum + b[j] * c[i + j];
    }
    c[i + m] = -sum / b[m];
  }
  return c;
}
} // namespace gns
