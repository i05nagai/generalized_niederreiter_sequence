#include "gns/matrix_func.h"

namespace gns {
template <int Base>
bool IsIdentity(const Matrix<Base>& matrix)
{
  for (size_t row = 0; row < matrix.RowSize(); ++row) {
    for (size_t col = 0; col < matrix.ColSize(); ++col) {
      // anti diagonal
      if (row != col) {
        if (matrix(row, col) != 0) {
          return false;
        }
      } else {
        if (matrix(row, col) != 1) {
          return false;
        }
      }
    }
  }
  return true;
}
} // namespace gns

namespace gns {
#define TEMPLATE_INSTANTIATION(Base) \
  template\
  bool IsIdentity(const Matrix<Base>& matrix);

TEMPLATE_INSTANTIATION(2);
TEMPLATE_INSTANTIATION(4);
TEMPLATE_INSTANTIATION(16);
} // namespace gns
