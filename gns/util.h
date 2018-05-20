#pragma once
#include <cassert>
#include <cmath>
#include <iterator>
#include <memory>
#include <vector>
#include "gns/galois_field.h"
#include "gns/vector.h"

namespace gns {
template <typename T>
inline std::reverse_iterator<T*> rbegin(T* v) {
  return std::reverse_iterator<T*>(v);
}

template <typename T>
inline std::reverse_iterator<T*> rend(T* v) {
  return std::reverse_iterator<T*>(v);
}
/**
 * @brief Calcualte digit expressed in base2
 *
 * @tparam Base
 * @param num
 *
 * @return digit
 */
template <int Base>
inline size_t CalculateDigit(size_t num) {
  assert(num > 0);
  return std::log(num) / std::log(Base) + 1;
}
/**
 * @brief Calcualte degree as polynomial in Base
 *
 * @tparam Base
 * @param num
 *
 * @return degree
 */
template <int Base>
inline size_t CalculateDegree(size_t num) {
  assert(num > 0);
  return CalculateDigit<Base>(num) - 1;
}

template <int Base>
inline std::pair<size_t, std::unique_ptr<GaloisField<Base>[]>>
CalculateBaseAdic(size_t num) {
  assert(num > 0);

  const size_t digit = CalculateDigit<Base>(num);
  std::unique_ptr<GaloisField<Base>[]> data(new GaloisField<Base>[digit]);
  for (size_t i = 0; i < digit; ++i) {
    data[i] = num % Base;
    num = static_cast<size_t>(num / Base);
  }
  return std::make_pair(digit, std::move(data));
}

template <int Base>
inline double BaseAdicToDouble(const Vector<Base>& base_adic) {
  double point = 0.0;
  double divisor = Base;
  for (size_t i = 0; i < base_adic.Size(); ++i) {
    point += base_adic[i].value() / divisor;
    divisor *= static_cast<double>(Base);
  }
  return point;
}

/**
   @brief
    Assuming $p=2$.  Let $n$ be num.
    Base $p$ expansion of $n$ is given by
    $$n = \sum_{i=0}^{N-1} a_{k}p^{k}$$, $$a_{k} \in \{0, \ldots, p-1\}$$.
    This function returns $\alpha(n)$ which is defined by

    $$
     \alpha(n)
     :=
     \min
     \{
       k \ge 0
       \mid
       a_{k} \neq p - 1 = 1
     \}
    $$

   @tparam Base
   @param num is from 0 to Base - 1.

   @return $$\sum_{k=0}^{\alpha(n)}x^{k}$
 */
template <int Base>
inline size_t FindCarryBit(size_t num) {
  const size_t num_digit = std::log2(Base);
  // num = (a_{N-1} ... a_{0})_{2}
  // alpha(num)
  for (size_t i = 0; i < num_digit; ++i) {
    const size_t a = (num >> i) & 1;
    if (a != 0) {
      return (2 << i) - 1;
    }
  }
  return (2 << (num_digit - 1)) - 1;
}

template <int Base>
inline size_t BitRightShift(const size_t num);

template <>
inline size_t BitRightShift<2>(const size_t num) {
  return num >> 1;
}

template <>
inline size_t BitRightShift<4>(const size_t num) {
  return num >> 2;
}

template <>
inline size_t BitRightShift<16>(const size_t num) {
  return num >> 4;
}

}  // namespace gns
