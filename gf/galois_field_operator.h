#pragma once
#include "fwd.h"
#include <cassert>

namespace gf {
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
      const unsigned char left, const unsigned char right)
  {
    return left ^ right;
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
  inline unsigned char sub(
      const unsigned char left, const unsigned char right)
  {
    return left ^ right;
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
  inline unsigned char mult(
      const unsigned char left, const unsigned char right)
  {
    /*
    static unsigned char multTable[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,2,4,6,8,10,12,14,15,13,11,9,7,5,3,1,0,3,6,5,12,15,10,9,7,4,1,2,11,8,13,14,0,4,8,12,15,11,7,3,1,5,9,13,14,10,6,2,0,5,10,15,11,14,1,4,9,12,3,6,2,7,8,13,0,6,12,10,7,1,11,13,14,8,2,4,9,15,5,3,0,7,14,9,3,4,13,10,6,1,8,15,5,2,11,12,0,8,15,7,1,9,14,6,2,10,13,5,3,11,12,4,0,9,13,4,5,12,8,1,10,3,7,14,15,6,2,11,0,10,11,1,9,3,2,8,13,7,6,12,4,14,15,5,0,11,9,2,13,6,4,15,5,14,12,7,8,3,1,10,0,12,7,11,14,2,9,5,3,15,4,8,13,1,10,6,0,13,5,8,10,7,15,2,11,6,14,3,1,12,4,9,0,14,3,13,6,8,5,11,12,2,15,1,10,4,9,7,0,15,1,14,2,13,3,12,4,11,5,10,6,9,7,8};
    static unsigned char base = 16; 
    return multTable[base * left + right];
    */
    return left & right;
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
  inline unsigned char inv(const unsigned char val)
  {
    /*
    static unsigned char invTable[] = {0,1,15,10,8,6,5,9,4,7,3,14,13,12,11,2};
    */
    static unsigned char invTable[] = {0, 1};
    return invTable[static_cast<int>(val)];
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
  inline unsigned char div(
      const unsigned char left, const unsigned char right)
  {
    assert(right > 0);
    return mult<N>(left, inv<N>(right));
  }
  
  /**
  inline unsigned char operator +(
      const unsigned char left, const unsigned char right)
  {
    return left ^ right;
  }
  inline unsigned char operator -(
      const unsigned char left, const unsigned char right)
  {
    return left ^ right;
  }
  inline unsigned char operator *(
      const unsigned char left, const unsigned char right)
  {
    static unsigned char multTable[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,2,4,6,8,10,12,14,15,13,11,9,7,5,3,1,0,3,6,5,12,15,10,9,7,4,1,2,11,8,13,14,0,4,8,12,15,11,7,3,1,5,9,13,14,10,6,2,0,5,10,15,11,14,1,4,9,12,3,6,2,7,8,13,0,6,12,10,7,1,11,13,14,8,2,4,9,15,5,3,0,7,14,9,3,4,13,10,6,1,8,15,5,2,11,12,0,8,15,7,1,9,14,6,2,10,13,5,3,11,12,4,0,9,13,4,5,12,8,1,10,3,7,14,15,6,2,11,0,10,11,1,9,3,2,8,13,7,6,12,4,14,15,5,0,11,9,2,13,6,4,15,5,14,12,7,8,3,1,10,0,12,7,11,14,2,9,5,3,15,4,8,13,1,10,6,0,13,5,8,10,7,15,2,11,6,14,3,1,12,4,9,0,14,3,13,6,8,5,11,12,2,15,1,10,4,9,7,0,15,1,14,2,13,3,12,4,11,5,10,6,9,7,8};
    static unsigned char base = 16; 
    return multTable[base * left + right];
  }
  inline unsigned char operator /(
      const unsigned char left, const unsigned char right)
  {
    static unsigned char invTable[] = {0,1,15,10,8,6,5,9,4,7,3,14,13,12,11,2};
    return left * invTable[static_cast<int>(right)];
  }
  */
} // namespace gf
