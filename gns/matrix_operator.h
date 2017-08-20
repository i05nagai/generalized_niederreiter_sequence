#pragma once
#include "gns/matrix.h"
#include "gns/vector.h"
#include <cassert>

namespace gns {
  /**
   * @brief 
   *
   * @tparam Base
   * @param m
   * @param v
   *
   * @return 
   */
template <int Base>
Vector<Base> operator*(const Matrix<Base>& m, const Vector<Base>& v) {
  assert(0 < m.ColSize());
  assert(0 < v.Size());
  const size_t size = std::min(m.ColSize(), v.Size());

  Vector<Base> result(m.RowSize());
  for (size_t row = 0; row < m.RowSize(); ++row) {
    GaloisField<Base> sum = 0;
    for (size_t col = 0; col < size; ++col) {
      sum = sum + m(row, col) * v(col);
    }
    result(row) = sum;
  }
  return result;
}

}  // namespace gns
