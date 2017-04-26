#pragma once

namespace gf {
  /*--------------------------------------------------------------------------
   * galois_field_operator.h
   *------------------------------------------------------------------------*/
  template <int N>
  inline unsigned char getLowestSiginicantBit(
      const unsigned char value, const int base);
  template <int N>
  inline unsigned char add(
      const unsigned char left, const unsigned char right);
  template <int N>
  inline unsigned char sub(
      const unsigned char left, const unsigned char right);
  template <int N>
  inline unsigned char sub(
      const unsigned char left, const unsigned char right);
  template <int N>
  inline unsigned char mult(
      const unsigned char left, const unsigned char right);
  template <int N>
  inline unsigned char inv(const unsigned char val);
  template <int N>
  inline unsigned char div(
      const unsigned char left, const unsigned char right);
} // namespace gf
