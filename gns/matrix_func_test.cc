#include "gns/matrix_func.h"
#include <gtest/gtest.h>

namespace gns {
TEST(matrix_func_test, IsIdentity)
{
  // not identity
  {
    Matrix<2> m(2, 2);
    m(0, 0) = 1;
    m(0, 1) = 1;
    m(1, 0) = 0;
    m(1, 1) = 1;

    EXPECT_FALSE(IsIdentity(m));
  }
  // identity
  {
    Matrix<2> m(2, 2);
    m(0, 0) = 1;
    m(0, 1) = 0;
    m(1, 0) = 0;
    m(1, 1) = 1;

    EXPECT_TRUE(IsIdentity(m));
  }
}
} // namespace gns
