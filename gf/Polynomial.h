#pragma once
#include "gf/galois_field_operator.h"
#include <memory>
#include <string>

namespace gf {
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
  /**
   * @brief 
   *
   * @tparam N number of elements in finite filed $F_{N}$
   */
  template <int N = 2>
  class Polynomial {
  public:
    typedef unsigned char* iterator;
    typedef const unsigned char* const_iterator;
  public:
    /**
     * @brief 
     */
    explicit Polynomial();
    /**
     * @brief 
     *
     * @param degree
     */
    Polynomial(const size_t degree);
    /**
     * @brief 
     *
     * @param coeffs[]
     */
    Polynomial(std::initializer_list<unsigned char> coeffs);
    /**
     * @brief 
     *
     * @param size
     * @param coeffs
     */
    Polynomial(
      const size_t size,
      std::unique_ptr<unsigned char[]> coeffs);
    /**
     * @brief 
     *
     * @param other
     */
    Polynomial(const Polynomial<N>& other);
    /**
     * @brief 
     */
    ~Polynomial();
    /**
     * @brief 
     *
     * @param other
     *
     * @return 
     */
    Polynomial& operator =(const Polynomial<N>& other);
    /**
     * @brief 
     *
     * @param other
     *
     * @return 
     */
    bool operator==(const Polynomial<N>& other);
    /**
     * @brief 
     *
     * @param other
     *
     * @return 
     */
    bool operator==(const Polynomial<N>& other) const;
    /**
     * @brief 
     *
     * @param other
     *
     * @return 
     */
    Polynomial& operator =(Polynomial<N>&& other);
    /**
     * @brief 
     *
     * @param other
     *
     * @return 
     */
    Polynomial& operator+=(const Polynomial<N>& other);
    /**
     * @brief 
     *
     * @param other
     *
     * @return 
     */
    Polynomial& operator-=(const Polynomial<N>& other);
    /**
     * @brief 
     *
     * @param a
     *
     * @return 
     */
    Polynomial& operator*=(const unsigned char a);
    /**
     * @brief 
     *
     * @param other
     *
     * @return 
     */
    Polynomial& operator*=(const Polynomial<N>& other);
    /**
     * @brief 
     *
     * @return 
     */
    bool isZero() const;
    /**
     * @brief 
     *
     * @param degree degree of polynominal.
     */
    void resize(const size_t degree);
    /**
     * @brief 
     */
    void toZero();
    /**
     * @brief Convert to string.
     *
     * @return 
     */
    std::string toString(
        const EnumPolynomialExpression expressionType = POLYNOMIAL) const;
    /**
     * @brief 
     *
     * @return 
     */
    inline unsigned char last() const
    {
      return coeffs_[degree_ + 1];
    }
    /**
     * @brief 
     *
     * @return 
     */
    inline size_t getDegree() const
    {
      return degree_;
    }
    /**
     * @brief 
     *
     * @param index
     *
     * @return 
     */
    inline unsigned char& operator[](const size_t index)
    {
      return coeffs_[index];
    }
    /**
     * @brief 
     *
     * @param index
     *
     * @return 
     */
    inline const unsigned char& operator[](const size_t index) const
    {
      return coeffs_[index];
    }
    /**
     * @brief 
     *
     * @return 
     */
    inline iterator begin()
    {
      return coeffs_.get();
    }
    /**
     * @brief 
     *
     * @return 
     */
    inline const_iterator begin() const
    {
      return coeffs_.get();
    }
    /**
     * @brief 
     *
     * @return 
     */
    inline const_iterator cbegin() const
    {
      return coeffs_.get();
    }
    /**
     * @brief 
     *
     * @return 
     */
    inline iterator end()
    {
      return coeffs_.get() + degree_ + 1;
    }
    /**
     * @brief 
     *
     * @return 
     */
    inline const_iterator end() const
    {
      return coeffs_.get() + degree_ + 1;
    }
    /**
     * @brief 
     *
     * @return 
     */
    inline const_iterator cend() const
    {
      return coeffs_.get() + degree_ + 1;
    }
  private:
    size_t degree_;
    std::unique_ptr<unsigned char[]> coeffs_;
  };
  /*--------------------------------------------------------------------------
   * free functions
   *------------------------------------------------------------------------*/
  /**
   * @brief This calculates quotinent and remainder 
   *  as satisfy following equation.
   *
   *  dividend = divisor * quotient + remainder
   *
   * @tparam N
   * @param dividend
   * @param divisor
   * @param quotient
   * @param remainder
   *
   * @return first is quotient, second is remainder.
   */
  template <int N>
  std::pair<Polynomial<N>, Polynomial<N>>
  euclidean_division(
      const Polynomial<N>& dividend,
      const Polynomial<N>& divisor);
  template <int N>
  Polynomial<N>
  toPolynomial(const char* strData);
} // namespace gf
