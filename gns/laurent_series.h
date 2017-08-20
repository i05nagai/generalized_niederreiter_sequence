#pragma once
#include "gns/polynomial.h"
#include <cassert>
#include <memory>

namespace gns {
/**
 * @brief 
 *  Solve the first part of equations up to array_size.
 *
 * @tparam Base
 * @param a
 * @param b
 * @param c
 * @param array_size
 *
 * @return the number of array size after solving equations.
 *  Negative value/zero means no space left.
 */
template <int Base>
int
LaurentSeriesDivisionFirstEquations(
    const GaloisFieldPolynomial<Base>& a, const GaloisFieldPolynomial<Base>& b,
    std::unique_ptr<GaloisField<Base>[]>& c,
    const size_t array_size)
{
  const size_t n = a.degree();
  const size_t m = b.degree();
  const size_t num_equations = -(-m + n + 1);
  const int array_room = array_size - num_equations;
  if (num_equations > array_size) {
    return array_room;
  }
  // first part equations
  for (size_t i = 0; i < num_equations; ++i) {
    c[i] = 0;
  }
  return array_room;
}
/**
 * @brief 
 *  Solve the second part of equations up to array_size.
 *
 * @tparam Base
 * @param a
 * @param b
 * @param c
 * @param array_room from 1 to maximum array size.
 *
 * @return The number of room for array after solving equations.
 *  Negative value/zero means no space left.
 */
template <int Base>
int LaurentSeriesDivisionSecondEquations(
    const GaloisFieldPolynomial<Base>& a, const GaloisFieldPolynomial<Base>& b,
    std::unique_ptr<GaloisField<Base>[]>& c,
    const size_t array_room)
{
  assert(array_room > 0);
  const size_t n = a.degree();
  const size_t m = b.degree();
  const size_t num_equations = n + 1;
  int end = 0;
  if (num_equations > array_room) {
    end = n - (array_room - 1);
  }
  // first part equations
  for (int k = n; k >= end; --k) {
    GaloisField<Base> sum(0);
    for (size_t j = 1; j <= n - k; ++j) {
      sum = sum + b[m - j] * c[-(-m + k + j)];
    }
    c[-(-m + k)] = (a[k] - sum) / b[m];
  }
  return array_room - num_equations;
}
/**
 * @brief Solve equiations and substitute the solution up to array_size.
 *
 * @tparam Base
 * @param a
 * @param b
 * @param c
 * @param array_size the size of array c.
 *
 */
template <int Base>
void LaurentSeriesDivisionLastEquations(
    const GaloisFieldPolynomial<Base>& a, const GaloisFieldPolynomial<Base>& b,
    std::unique_ptr<GaloisField<Base>[]>& c,
    const size_t array_size)
{
  const size_t m = b.degree();
  const size_t array_room_left = array_size - m;
  // third part equations
  for (size_t i = 1; i < array_room_left; ++i) {
    // sum
    GaloisField<Base> sum(0);
    for (size_t j = 0; j < m; ++j) {
      sum = sum + b[j] * c[i + j];
    }
    // solve the quiation up to array_size
    c[i + m] = -sum / b[m];
  }
}
/**
 * @brief
 *
 * @tparam Base
 * @param a
 * @param b
 * @param max_degree
 *
 * @return
 */
template <int Base>
std::unique_ptr<GaloisField<Base>[]> SolveLaurentSeriesDivision(
    const GaloisFieldPolynomial<Base>& a, const GaloisFieldPolynomial<Base>& b,
    const size_t max_degree) {
  const size_t n = a.degree();
  const size_t m = b.degree();
  assert(n < m);
  const size_t array_size = max_degree + 1;
  std::unique_ptr<GaloisField<Base>[]> c(new GaloisField<Base>[array_size]);
  // calculate c = a / b
  // assuming m := deg(a) < deg(b) =: n

  int array_room = LaurentSeriesDivisionFirstEquations(a, b, c, array_size);
  if (array_room <= 0) {
    return c;
  }
  array_room = LaurentSeriesDivisionSecondEquations(a, b, c, array_room);
  if (array_room <= 0) {
    return c;
  }
  LaurentSeriesDivisionLastEquations(a, b, c, array_size);
  return c;
}
} // namespace gns
