#pragma once
#include "gns/galois_field.h"
#include <memory>

/*--------------------------------------------------------------------------
 * operators
 *------------------------------------------------------------------------*/
namespace gns {
  /**
   * @brief 
   *
   * @param value
   * @param base
   *
   * @return 
   */
  template <int N>
  inline unsigned char getLowestSiginicantBit(
      const unsigned char value, const int base)
  {
    return value & (base - 1);
  }
  /**
   * @brief 
   *
   * @param left
   * @param right
   *
   * @return 
   */
  template <int N>
  inline unsigned char add(
      const unsigned char left, const unsigned char right);
  /**
   * @brief 
   *
   * @param left
   * @param right
   *
   * @return 
   */
  template <int N>
  inline unsigned char sub(
      const unsigned char left, const unsigned char right);
  /**
   * @brief 
   *
   * @param left
   * @param right
   *
   * @return 
   */
  template <int N>
  inline unsigned char mult(
      const unsigned char left, const unsigned char right);
  /**
   * @brief 
   *
   * @param left
   * @param right
   *
   * @return 
   */
  template <int N>
  inline unsigned char div(
      const unsigned char left, const unsigned char right);

  /*--------------------------------------------------------------------------
   * Base=2
   *------------------------------------------------------------------------*/
  template <>
  inline
  unsigned char add<2>(
      const unsigned char left, const unsigned char right)
  {
    return left ^ right;
  }

  template <>
  inline
  unsigned char sub<2>(
      const unsigned char left, const unsigned char right)
  {
    return left ^ right;
  }

  template <>
  inline
  unsigned char mult<2>(
      const unsigned char left, const unsigned char right)
  {
    return left & right;
  }

  template <>
  inline
  unsigned char div<2>(const unsigned char left, const unsigned char right)
  {
    static unsigned char inv_table[] = {0, 1};
    return left * inv_table[static_cast<int>(right)];
  }

  /*--------------------------------------------------------------------------
   * Base=4
   *------------------------------------------------------------------------*/

  template <>
  inline
  unsigned char add<4>(
      const unsigned char left, const unsigned char right)
  {
    return left ^ right;
  }

  template <>
  inline
  unsigned char sub<4>(
      const unsigned char left, const unsigned char right)
  {
    return left ^ right;
  }

  template <>
  inline
  unsigned char mult<4>(
      const unsigned char left, const unsigned char right)
  {
    static const unsigned int mult_table[] = {
      0, 0, 0, 0,
      0, 1, 2, 3,
      0, 2, 3, 1,
      0, 3, 1, 2
    };
    static unsigned char base = 16;
    return mult_table[base * left + right];
  }

  template <>
  inline
  unsigned char div<4>(const unsigned char left, const unsigned char right)
  {
    static unsigned char inv_table[] = {0, 1, 3, 2};
    return left * inv_table[static_cast<int>(right)];
  }

  /*--------------------------------------------------------------------------
   * Base=16
   *------------------------------------------------------------------------*/

  template <>
  inline
  unsigned char add<16>(
      const unsigned char left, const unsigned char right)
  {
    return left ^ right;
  }

  template <>
  inline
  unsigned char sub<16>(
      const unsigned char left, const unsigned char right)
  {
    return left ^ right;
  }

  template <>
  inline
  unsigned char mult<16>(
      const unsigned char left, const unsigned char right)
  {
    static const unsigned char mult_table[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
      0, 2, 4, 6, 8, 10, 12, 14, 15, 13, 11, 9, 7, 5, 3, 1,
      0, 3, 6, 5, 12, 15, 10, 9, 7, 4, 1, 2, 11, 8, 13, 14,
      0, 4, 8, 12, 15, 11, 7, 3, 1, 5, 9, 13, 14, 10, 6, 2,
      0, 5, 10, 15, 11, 14, 1, 4, 9, 12, 3, 6, 2, 7, 8, 13,
      0, 6, 12, 10, 7, 1, 11, 13, 14, 8, 2, 4, 9, 15, 5, 3,
      0, 7, 14, 9, 3, 4, 13, 10, 6, 1, 8, 15, 5, 2, 11, 12,
      0, 8, 15, 7, 1, 9, 14, 6, 2, 10, 13, 5, 3, 11, 12, 4,
      0, 9, 13, 4, 5, 12, 8, 1, 10, 3, 7, 14, 15, 6, 2, 11,
      0, 10, 11, 1, 9, 3, 2, 8, 13, 7, 6, 12, 4, 14, 15, 5,
      0, 11, 9, 2, 13, 6, 4, 15, 5, 14, 12, 7, 8, 3, 1, 10,
      0, 12, 7, 11, 14, 2, 9, 5, 3, 15, 4, 8, 13, 1, 10, 6,
      0, 13, 5, 8, 10, 7, 15, 2, 11, 6, 14, 3, 1, 12, 4, 9,
      0, 14, 3, 13, 6, 8, 5, 11, 12, 2, 15, 1, 10, 4, 9, 7,
      0, 15, 1, 14, 2, 13, 3, 12, 4, 11, 5, 10, 6, 9, 7, 8
    };
    static unsigned char base = 16;
    return mult_table[base * left + right];
  }

  template <>
  inline
  unsigned char div<16>(const unsigned char left, const unsigned char right)
  {
    static unsigned char inv_table[] = {0,1,15,10,8,6,5,9,4,7,3,14,13,12,11,2};
    return left * inv_table[static_cast<int>(right)];
  }
}

namespace gns {
// binary operator
template<int Base>
std::ostream& operator<<(std::ostream& os, const GaloisField<Base>& x)
{
  os << x.value();
  return os;
}

template <int Base>
GaloisField<Base>
operator +(const GaloisField<Base>& e1, const GaloisField<Base>& e2);

template <int Base>
GaloisField<Base>
operator +(const GaloisField<Base>& e1, const unsigned int e2);

template <int Base>
GaloisField<Base>
operator +(const unsigned int e1, const GaloisField<Base>& e2);

template <int Base>
GaloisField<Base>
operator -(const GaloisField<Base>& e1, const GaloisField<Base>& e2);

template <int Base>
GaloisField<Base>
operator *(const GaloisField<Base>& e1, const GaloisField<Base>& e2);

template <int Base>
GaloisField<Base>
operator /(const GaloisField<Base>& e1, const GaloisField<Base>& e2);

// unary operator
template <int Base>
GaloisField<Base>
operator -(const GaloisField<Base>& e1);

/*--------------------------------------------------------------------------
 * Base=2
 *------------------------------------------------------------------------*/
template <>
inline
GaloisField<2>
operator +(const GaloisField<2>& e1, const GaloisField<2>& e2)
{
  return GaloisField<2>(e1.value() ^ e2.value());
}

template <>
inline
GaloisField<2>
operator +(const GaloisField<2>& e1, const unsigned int e2)
{
  assert(e2 < 2);
  return GaloisField<2>(e1.value() ^ e2);
}

template <>
inline
GaloisField<2>
operator +(const unsigned int e1, const GaloisField<2>& e2)
{
  assert(e1 < 2);
  return GaloisField<2>(e1 ^ e2.value());
}

template <>
inline
GaloisField<2>
operator -(const GaloisField<2>& e1, const GaloisField<2>& e2)
{
  return GaloisField<2>(e1.value() ^ e2.value());
}

template <>
inline
GaloisField<2>
operator *(const GaloisField<2>& e1, const GaloisField<2>& e2)
{
  return GaloisField<2>(e1.value() & e2.value());
}

template <>
inline
GaloisField<2>
operator /(const GaloisField<2>& e1, const GaloisField<2>& e2)
{
  return GaloisField<2>(e1.value() & e2.value());
}

template <>
inline
GaloisField<2>
operator -(const GaloisField<2>& e1)
{
  return GaloisField<2>(e1);
}

/*--------------------------------------------------------------------------
 * Base=4
 *------------------------------------------------------------------------*/
template <>
inline
GaloisField<4>
operator +(const GaloisField<4>& e1, const GaloisField<4>& e2)
{
  return GaloisField<4>(e1.value() ^ e2.value());
}

template <>
inline
GaloisField<4>
operator -(const GaloisField<4>& e1, const GaloisField<4>& e2)
{
  return GaloisField<4>(e1.value() ^ e2.value());
}

template <>
inline
GaloisField<4>
operator *(const GaloisField<4>& e1, const GaloisField<4>& e2)
{
    static const unsigned int mult_table[] = {
      0, 0, 0, 0,
      0, 1, 2, 3,
      0, 2, 3, 1,
      0, 3, 1, 2
    };
  return GaloisField<4>(mult_table[4 * e1.value() + e2.value()]);
}

template <>
inline
GaloisField<4>
operator /(const GaloisField<4>& e1, const GaloisField<4>& e2)
{
  static const unsigned int inv_table[] = {0, 1, 3, 2};
  return e1 * GaloisField<4>(inv_table[e2.value()]);
}

template <>
inline
GaloisField<4>
operator -(const GaloisField<4>& e1)
{
  return GaloisField<4>(e1);
}

/*--------------------------------------------------------------------------
 * Base=16
 *------------------------------------------------------------------------*/
template <>
inline
GaloisField<16>
operator +(const GaloisField<16>& e1, const GaloisField<16>& e2)
{
  return GaloisField<16>(e1.value() ^ e2.value());
}

template <>
inline
GaloisField<16>
operator -(const GaloisField<16>& e1, const GaloisField<16>& e2)
{
  return GaloisField<16>(e1.value() ^ e2.value());
}

template <>
inline
GaloisField<16>
operator *(const GaloisField<16>& e1, const GaloisField<16>& e2)
{
    static const unsigned int mult_table[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
      0, 2, 4, 6, 8, 10, 12, 14, 15, 13, 11, 9, 7, 5, 3, 1,
      0, 3, 6, 5, 12, 15, 10, 9, 7, 4, 1, 2, 11, 8, 13, 14,
      0, 4, 8, 12, 15, 11, 7, 3, 1, 5, 9, 13, 14, 10, 6, 2,
      0, 5, 10, 15, 11, 14, 1, 4, 9, 12, 3, 6, 2, 7, 8, 13,
      0, 6, 12, 10, 7, 1, 11, 13, 14, 8, 2, 4, 9, 15, 5, 3,
      0, 7, 14, 9, 3, 4, 13, 10, 6, 1, 8, 15, 5, 2, 11, 12,
      0, 8, 15, 7, 1, 9, 14, 6, 2, 10, 13, 5, 3, 11, 12, 4,
      0, 9, 13, 4, 5, 12, 8, 1, 10, 3, 7, 14, 15, 6, 2, 11,
      0, 10, 11, 1, 9, 3, 2, 8, 13, 7, 6, 12, 4, 14, 15, 5,
      0, 11, 9, 2, 13, 6, 4, 15, 5, 14, 12, 7, 8, 3, 1, 10,
      0, 12, 7, 11, 14, 2, 9, 5, 3, 15, 4, 8, 13, 1, 10, 6,
      0, 13, 5, 8, 10, 7, 15, 2, 11, 6, 14, 3, 1, 12, 4, 9,
      0, 14, 3, 13, 6, 8, 5, 11, 12, 2, 15, 1, 10, 4, 9, 7,
      0, 15, 1, 14, 2, 13, 3, 12, 4, 11, 5, 10, 6, 9, 7, 8
    };
  return GaloisField<16>(mult_table[16 * e1.value() + e2.value()]);
}

template <>
inline
GaloisField<16>
operator /(const GaloisField<16>& e1, const GaloisField<16>& e2)
{
  static const unsigned int inv_table[] = {
    0, 1, 15, 10, 8, 6, 5, 9, 4, 7, 3, 14, 13, 12, 11, 2
  };
  return e1 * GaloisField<16>(inv_table[e2.value()]);
}

template <>
inline
GaloisField<16>
operator -(const GaloisField<16>& e1)
{
  return GaloisField<16>(e1);
}
} // namespace gns
