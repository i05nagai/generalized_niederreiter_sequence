#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include "gns/galois_field.h"
#include "gns/galois_field_operator.h"
#include "gns/util.h"

namespace gns {
/**
 * @brief
 */
enum EnumPolynomialExpression {
  /**
   * @brief if base is 2, binary expression.
   *  If base is 16, this is same as hexadecimal expression.
   *  For example, base=16, coeffs = {0, 1, 0}.
   */
  INTEGER = 0,
  COEFFICIENTS,
  POLYNOMIAL,
};

template <int Base>
class GaloisFieldPolynomial {
  // private typedef
 private:
  // public typedef
 public:
  typedef GaloisField<Base> value_type;
  typedef GaloisField<Base>* iterator;
  typedef const GaloisField<Base>* const_iterator;
  // public function
 public:
  /**
   * @brief
   */
  inline explicit GaloisFieldPolynomial() : coeffs_(new GaloisField<Base>[1]) {}
  /**
   * @brief
   *
   * @param other
   */
  inline GaloisFieldPolynomial(const GaloisFieldPolynomial<Base>& other)
      : coeffs_(new GaloisField<Base>[other.degree_ + 1]),
        degree_(other.degree_) {
    std::copy(other.cbegin(), other.cend(), this->begin());
  }
  /**
   * @brief
   *
   * @param degree
   */
  inline GaloisFieldPolynomial(size_t degree)
      : coeffs_(new GaloisField<Base>[degree + 1]), degree_(degree) {}
  /**
   * @brief
   *
   * @param coeffs
   */
  inline GaloisFieldPolynomial(std::initializer_list<unsigned char> coeffs)
      : GaloisFieldPolynomial(coeffs.size() - 1) {
    std::copy(coeffs.begin(), coeffs.end(), coeffs_.get());
  }
  /**
   * @brief
   *
   * @param degree
   * @param coeffs
   */
  inline GaloisFieldPolynomial(const size_t degree,
                               std::unique_ptr<value_type[]> data)
      : coeffs_(std::move(data)), degree_(degree) {}
  /**
   * @brief
   */
  inline ~GaloisFieldPolynomial() {}
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  inline bool operator==(const GaloisFieldPolynomial<Base>& other) {
    return degree_ == other.degree_ &&
           std::equal(other.cbegin(), other.cend(), this->cbegin());
  }
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  inline bool operator==(const GaloisFieldPolynomial<Base>& other) const {
    return const_cast<GaloisFieldPolynomial&>(*this) == other;
  }
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  inline GaloisFieldPolynomial& operator=(
      const GaloisFieldPolynomial<Base>& other) {
    // self assignment
    if (&other == this) {
      return *this;
    }
    coeffs_ = new GaloisField<Base>[other.degree_ + 1];
    std::copy(other.cbegin(), other.cend(), this->begin());
    return *this;
  }
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  inline GaloisFieldPolynomial& operator=(GaloisFieldPolynomial<Base>&& other) {
    // self assignment never happens?
    degree_ = other.degree_;
    coeffs_ = std::move(other.coeffs_);
    other.coeffs_ = nullptr;
    return *this;
  }
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  inline GaloisFieldPolynomial& operator+=(
      const GaloisFieldPolynomial<Base>& other) {
    const size_t other_degree = other.degree();

    size_t degree = 0;
    if (degree_ <= other_degree) {
      const size_t min_degree = degree_;
      degree = other_degree;
      std::unique_ptr<value_type[]> temp(new value_type[degree + 1]);

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
      std::unique_ptr<value_type[]> temp(new value_type[degree + 1]);

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
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  GaloisFieldPolynomial& operator-=(const GaloisFieldPolynomial<Base>& other) {
    const size_t other_degree = other.degree();

    size_t degree = 0;
    if (degree_ <= other_degree) {
      const size_t min_degree = degree_;
      degree = other_degree;
      std::unique_ptr<GaloisField<Base>[]> temp(
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
  /**
   * @brief
   *
   * @param multiplier
   *
   * @return
   */
  GaloisFieldPolynomial& operator*=(const unsigned int multiplier) {
    if (multiplier != 0) {
      const GaloisField<Base> mult(multiplier);
      for (size_t i = 0; i < degree_ + 1; ++i) {
        coeffs_[i] = mult * coeffs_[i];
      }
    } else {
      std::unique_ptr<GaloisField<Base>[]> temp(new GaloisField<Base>[1]);
      this->replace_coeffs(temp, 0);
    }
    return *this;
  }
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  GaloisFieldPolynomial& operator*=(const GaloisFieldPolynomial<Base>& other) {
    if (other.IsZero() == true) {
      std::unique_ptr<value_type[]> temp(new value_type[1]);
      this->replace_coeffs(temp, 0);
    } else {
      const size_t other_degree = other.degree();
      const size_t degree = degree_ + other_degree;
      std::unique_ptr<value_type[]> temp(new value_type[degree + 1]);
      std::fill(temp.get(), temp.get() + degree + 1, 0);
      for (size_t i = 0; i < degree_ + 1; ++i) {
        for (size_t j = 0; j < other_degree + 1; ++j) {
          temp[i + j] = temp[i + j] + coeffs_[i] * other[j];
        }
      }
      this->replace_coeffs(temp, degree);
    }
    return *this;
  }
  /**
   * @brief
   *
   * @return
   */
  inline bool IsZero() const {
    const bool is_zero =
        std::all_of(this->cbegin(), this->cend(),
                    [](const GaloisField<Base>& x) { return x == 0; });
    return is_zero;
  }
  /**
   * @brief
   *
   * @param index
   *
   * @return
   */
  inline GaloisField<Base>& operator[](const size_t index) {
    return coeffs_[index];
  }
  /**
   * @brief
   *
   * @param index
   *
   * @return
   */
  inline const GaloisField<Base>& operator[](const size_t index) const {
    return coeffs_[index];
  }
  /**
   * @brief
   *
   * @return
   */
  inline size_t degree() { return degree_; }
  /**
   * @brief
   *
   * @return
   */
  inline size_t degree() const { return degree_; }
  /**
   * @brief
   *
   * @return
   */
  inline iterator begin() { return coeffs_.get(); }
  /**
   * @brief
   *
   * @return
   */
  inline const_iterator begin() const { return coeffs_.get(); }
  /**
   * @brief
   *
   * @return
   */
  inline const_iterator cbegin() const { return coeffs_.get(); }
  /**
   * @brief
   *
   * @return
   */
  inline iterator end() { return coeffs_.get() + degree_ + 1; }
  /**
   * @brief
   *
   * @return
   */
  inline const_iterator end() const { return coeffs_.get() + degree_ + 1; }
  /**
   * @brief
   *
   * @return
   */
  inline const_iterator cend() const { return coeffs_.get() + degree_ + 1; }
  /**
   * @brief
   *
   * @param expressionType
   *
   * @return
   */
  std::string ToString(const EnumPolynomialExpression expression_type) const {
    if (expression_type == EnumPolynomialExpression::INTEGER) {
      // how many bit need to explain base
      const int base_bits = std::log2(Base);
      // coeffs into int
      long long int data = std::accumulate(
          gns::rbegin(coeffs_.get() + degree_ + 1), gns::rend(coeffs_.get()),
          0LL, [&base_bits](long long int a, const GaloisField<Base>& b) {
            return (a << base_bits) + b.value();
          });
      return std::to_string(data);
    } else if (expression_type == EnumPolynomialExpression::COEFFICIENTS) {
      return std::accumulate(coeffs_.get() + 1, coeffs_.get() + degree_ + 1,
                             std::to_string(coeffs_[0].value()),
                             [](std::string a, const GaloisField<Base>& b) {
                               return std::to_string(b.value()) + "  " + a;
                             });
    } else {
      std::string data = std::to_string(coeffs_[0].value());
      for (size_t i = 1; i < degree_ + 1; ++i) {
        data = std::to_string(coeffs_[i].value()) + "X^{" + std::to_string(i) +
               "} + " + data;
      }
      return data;
    }
  }

  // private function
 private:
  /**
   * @brief
   *
   * @param coeffs
   * @param degree
   */
  inline void replace_coeffs(const std::unique_ptr<value_type[]>& coeffs,
                             size_t degree) {
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

  // private members
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
template <int Base>
std::ostream& operator<<(std::ostream& os,
                         const GaloisFieldPolynomial<Base>& x) {
  std::string data = std::to_string(x[0].value());
  for (size_t i = 1; i < x.degree() + 1; ++i) {
    data = std::to_string(x[i].value()) + "X^{" + std::to_string(i) + "} + " +
           data;
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
GaloisFieldPolynomial<Base> MakeBasePolynomial(const size_t degree,
                                               const GaloisField<Base>& coeff) {
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
EuclideanDivision(const GaloisFieldPolynomial<Base>& dividend,
                  const GaloisFieldPolynomial<Base>& divisor) {
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
    if (residual.IsZero()) {
      break;
    }
  }
  // quaotient, residual
  return std::make_pair(quotient, residual);
}
}  // namespace gns
