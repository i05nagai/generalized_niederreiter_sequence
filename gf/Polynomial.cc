#include "gf/Polynomial.h"
#include "gf/util.h"
#include <algorithm>
#include <cmath>
#include <iterator>
#include <memory>
#include <numeric>

namespace gf {
  template <int N>
  Polynomial<N>::Polynomial()
  : degree_(0),
    coeffs_(new unsigned char[1])
  {
  }

  template <int N>
  Polynomial<N>::Polynomial(const size_t degree)
  : degree_(degree),
    coeffs_(new unsigned char[degree + 1])
  {
    std::fill(this->begin(), this->end(), 0);
  }

  template <int N>
  Polynomial<N>::Polynomial(std::initializer_list<unsigned char> coeffs)
  : Polynomial<N>(coeffs.size() - 1)
  {
    std::copy(coeffs.begin(), coeffs.end(), coeffs_.get());
  }

  template <int N>
  Polynomial<N>::Polynomial(
      const size_t size,
      std::unique_ptr<unsigned char[]> coeffs)
  : Polynomial<N>(size - 1)
  {
    std::copy(coeffs.get(), coeffs.get() + size, coeffs_.get());
  }

  template <int N>
  Polynomial<N>::Polynomial(const Polynomial& other)
  : degree_(other.degree_),
    coeffs_(new unsigned char[other.degree_ + 1])
  {
    std::copy(other.cbegin(), other.cend(), this->begin());
  }

  template <int N>
  Polynomial<N>::~Polynomial()
  {
  }

  template <int N>
  Polynomial<N>& Polynomial<N>::operator =(const Polynomial& other)
  {
    //self assignment
    if (&other == this) {
      return *this;
    }
    this->resize(other.degree_);
    std::copy(other.cbegin(), other.cend(), this->begin());
    return *this;
  }

  template <int N>
  Polynomial<N>& Polynomial<N>::operator =(Polynomial&& other)
  {
    //self assignment never happens?
    degree_ = other.degree_;
    coeffs_ = std::move(other.coeffs_);
    other.coeffs_ = nullptr;
    return *this;
  }

  template <int N>
  bool Polynomial<N>::operator==(const Polynomial& other)
  {
    return degree_ == other.degree_
      && std::equal(other.cbegin(), other.cend(), this->cbegin());
  }

  template <int N>
  bool Polynomial<N>::operator==(const Polynomial& other) const
  {
    return const_cast<Polynomial&>(*this) == other;
  }

  template <int N>
  Polynomial<N>& Polynomial<N>::operator+=(const Polynomial& other)
  {
    const size_t otherDegree = other.getDegree();
    
    size_t degree = 0;
    if (degree_ <= otherDegree) {
      const size_t minDegree = degree_;
      degree = otherDegree;
      std::unique_ptr<unsigned char[]> temp(new unsigned char[degree + 1]);

      // 0 to minDegree
      for (size_t i = 0; i < minDegree + 1; ++i) {
        temp[i] = add<N>(coeffs_[i], other[i]);
      }
      // minDegree + 1 to maxDegree
      for (size_t i = minDegree + 1; i < degree + 1; ++i) {
        temp[i] = add<N>(0, other[i]);
      }
      coeffs_.swap(temp);
    } else {
      const size_t minDegree = otherDegree;
      degree = degree_;
      std::unique_ptr<unsigned char[]> temp(new unsigned char[degree + 1]);

      for (size_t i = 0; i < minDegree + 1; ++i) {
        temp[i] = add<N>(coeffs_[i], other[i]);
      }
      for (size_t i = minDegree + 1; i < degree + 1; ++i) {
        temp[i] = add<N>(coeffs_[i], 0);
      }
      coeffs_.swap(temp);
    }
    // resize requires degree_ has current size of coeffs_
    degree_ = degree;
    // shrink degree
    while (coeffs_[degree] == 0 && degree > 0) {
      --degree;
    }
    this->resize(degree);

    return *this;
  }

  template <int N>
  Polynomial<N>& Polynomial<N>::operator-=(const Polynomial& other)
  {
    const size_t otherDegree = other.getDegree();
    
    size_t degree = 0;
    if (degree_ <= otherDegree) {
      const size_t minDegree = degree_;
      degree = otherDegree;
      std::unique_ptr<unsigned char[]> temp(new unsigned char[degree + 1]);

      // 0 to minDegree
      for (size_t i = 0; i < minDegree + 1; ++i) {
        temp[i] = sub<N>(coeffs_[i], other[i]);
      }
      // minDegree + 1 to maxDegree
      for (size_t i = minDegree + 1; i < degree + 1; ++i) {
        temp[i] = sub<N>(0, other[i]);
      }
      coeffs_.swap(temp);
    } else {
      const size_t minDegree = otherDegree;
      degree = degree_;
      std::unique_ptr<unsigned char[]> temp(new unsigned char[degree + 1]);

      for (size_t i = 0; i < minDegree + 1; ++i) {
        temp[i] = sub<N>(coeffs_[i], other[i]);
      }
      for (size_t i = minDegree + 1; i < degree + 1; ++i) {
        temp[i] = sub<N>(coeffs_[i], 0);
      }
      coeffs_.swap(temp);
    }
    // resize requires degree_ has current size of coeffs_
    degree_ = degree;
    // calc correct shrink degree
    while (coeffs_[degree] == 0 && degree > 0) {
      --degree;
    }
    this->resize(degree);

    return *this;
  }

  template <int N>
  Polynomial<N>& Polynomial<N>::operator*=(const unsigned char multiplier)
  {
    if (multiplier != 0) {
      for (size_t i = 0; i < degree_ + 1; ++i) {
        coeffs_[i] = mult<N>(multiplier, coeffs_[i]);
      }
    } else {
      this->toZero();
    }
    return *this;
  }

  template <int N>
  Polynomial<N>& Polynomial<N>::operator*=(const Polynomial& other)
  {
    if (other.isZero() == true) {
      this->toZero();
    } else {
      const size_t otherDegree = other.getDegree();
      std::unique_ptr<unsigned char[]> temp(
          new unsigned char[degree_ + otherDegree + 1]);
      std::fill(temp.get(), temp.get() + degree_ + otherDegree + 1, 0);
      for (size_t i = 0; i < degree_ + 1; ++i) {
        for (size_t j = 0; j < otherDegree + 1; ++j) {
          temp[i + j] = add<N>(temp[i + j], mult<N>(coeffs_[i], other[j]));
        }
      }
      coeffs_.swap(temp);
      degree_ += otherDegree;
    }
    return *this;
  }

  template <int N>
  bool Polynomial<N>::isZero() const
  {
    bool isZero = true;
    for (size_t i = 0; i < degree_ + 1; ++i) {
      if(coeffs_[i] != 0) {
        isZero = false;
      }
    }
    return isZero;
  }

  template <int N>
  void Polynomial<N>::resize(const size_t degree)
  {
    // shrink to degree
    if (degree < degree_) {
      std::unique_ptr<unsigned char[]> temp(new unsigned char[degree + 1]);
      std::copy(coeffs_.get(), coeffs_.get() + degree + 1, temp.get());
      coeffs_.swap(temp);
    // enlarge to degree
    } else {
      std::unique_ptr<unsigned char[]> temp(new unsigned char[degree + 1]);
      std::copy(coeffs_.get(), coeffs_.get() + degree_ + 1, temp.get());
      std::fill(temp.get() + degree_ + 1, temp.get() + degree + 1, 0);
      coeffs_.swap(temp);
    }
    degree_ = degree;
  }

  template <int N>
  void Polynomial<N>::toZero()
  {
    this->resize(0);
    coeffs_[0] = 0;
  }

  template <int N>
  std::string Polynomial<N>::toString(
      const EnumPolynomialExpression expressionType) const
  {
    if (expressionType == EnumPolynomialExpression::INTEGER) {
      // how many bit need to explain base
      const int baseBits = std::log2(N);
      // coeffs into int
      long long int data = std::accumulate(
          gf::rbegin(coeffs_.get() + degree_ + 1),
          gf::rend(coeffs_.get()),
          0LL,
          [&baseBits](long long int a, const unsigned char b) {
            return (a << baseBits) + b;
          });
      return std::to_string(data);
    } else if (expressionType == EnumPolynomialExpression::COEFFICIENTS) {
      return std::accumulate(coeffs_.get() + 1,
                             coeffs_.get() + degree_ + 1,
                             std::to_string(coeffs_[0]),
                             [](std::string a, const unsigned char b) {
                               return std::to_string(b) + "  " + a;
                             });
    } else {
      std::string data = std::to_string(coeffs_[0]);
      for (size_t i = 1; i < degree_ + 1; ++i) {
        data = std::to_string(coeffs_[i]) 
          + "X^{" 
          + std::to_string(i) 
          + "} + " 
          + data;
      }
      return data;
    }
  }
  /*--------------------------------------------------------------------------
   * free functions
   *------------------------------------------------------------------------*/
  template <int N>
  Polynomial<N> make_base_polynomial(
      const size_t degree, const unsigned char coeff)
  {
    Polynomial<N> polynomial(degree);
    polynomial[degree] = coeff;
    return polynomial;
  }

  template <int N>
  std::pair<Polynomial<N>, Polynomial<N>>
  euclidean_division(
      const Polynomial<N>& dividend,
      const Polynomial<N>& divisor)
  {
    Polynomial<N> tempDividend(dividend);
    const size_t divisorDegree = divisor.getDegree();
    Polynomial<N> quotient(tempDividend.getDegree() - divisorDegree);

    while (tempDividend.getDegree() >= divisorDegree) {
      const size_t degree = tempDividend.getDegree() - divisorDegree;
      const unsigned char dividendCoeff = tempDividend[tempDividend.getDegree()];
      const unsigned char divisorCoeff = divisor[divisorDegree];
      const unsigned char coeff = div<N>(dividendCoeff, divisorCoeff);
      Polynomial<N> temp = make_base_polynomial<N>(degree, coeff);
      quotient += temp;

      temp *= divisor;
      tempDividend -= temp; 
      if(tempDividend.isZero()) {
        break;
      }
    }
    return std::make_pair(quotient, tempDividend);
  }

  template <int N>
  Polynomial<N>
  toPolynomial(const char* strData)
  {
    size_t data = atoi(strData);
    std::pair<size_t, std::unique_ptr<unsigned char[]>> degreeAndCoeffs
      = calcBaseAdic<N>(data);
    const size_t& degree = degreeAndCoeffs.first;
    return Polynomial<N>(degree, std::move(degreeAndCoeffs.second));
  }
} // namespace gf

namespace gf {
  // N=2
  template
  Polynomial<2>::Polynomial();
  template
  Polynomial<2>::Polynomial(const size_t degree);
  template
  Polynomial<2>::Polynomial(std::initializer_list<unsigned char> coeffs);
  template
  Polynomial<2>::Polynomial(
      const size_t size,
      std::unique_ptr<unsigned char[]> coeffs);
  template
  Polynomial<2>::Polynomial(const Polynomial& other);
  template
  Polynomial<2>::~Polynomial();
  template
  Polynomial<2>& Polynomial<2>::operator =(const Polynomial& other);
  template
  Polynomial<2>& Polynomial<2>::operator =(Polynomial&& other);
  template
  bool
  Polynomial<2>::operator==(const Polynomial& other);
  template
  bool
  Polynomial<2>::operator==(const Polynomial& other) const;
  template
  Polynomial<2>&
  Polynomial<2>::operator+=(const Polynomial& other);
  template 
  Polynomial<2>&
  Polynomial<2>::operator-=(const Polynomial& other);
  template 
  Polynomial<2>&
  Polynomial<2>::operator*=(const unsigned char multiplier);
  template 
  Polynomial<2>&
  Polynomial<2>::operator*=(const Polynomial& other);
  template 
  bool
  Polynomial<2>::isZero() const;
  template
  void
  Polynomial<2>::resize(const size_t degree);
  template
  void
  Polynomial<2>::toZero();
  template
  std::string Polynomial<2>::toString(
      const EnumPolynomialExpression expressionType) const;
  /*--------------------------------------------------------------------------
   * free functions
   *------------------------------------------------------------------------*/
  template
  Polynomial<2> make_base_polynomial(
      const size_t degree, const unsigned char coeff);
  template
  std::pair<Polynomial<2>, Polynomial<2>>
  euclidean_division(
      const Polynomial<2>& dividend,
      const Polynomial<2>& divisor);
  template
  Polynomial<2>
  toPolynomial(const char* strData);
} // namespace gf
