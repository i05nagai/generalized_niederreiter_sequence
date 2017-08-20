#include "gns/matrix_operator.h"
#include <gtest/gtest.h>

namespace gns {
TEST(matrix_operator, OperatorMultiplyMatrixVectorTest)
{
  // 2x2 * 2
  {
    Vector<2> v({1, 1});
    Matrix<2> m(2, 2);
    m(0, 0) = 1;
    m(0, 1) = 1;
    m(1, 0) = 0;
    m(1, 1) = 1;

    Vector<2> actual = m * v;

    Vector<2> expect({0, 1});
    EXPECT_EQ(expect, actual);
  }
  // 2x2 * 1
  {
    Vector<2> v({1});
    Matrix<2> m(2, 2);
    m(0, 0) = 1;
    m(0, 1) = 1;
    m(1, 0) = 0;
    m(1, 1) = 1;

    Vector<2> actual = m * v;

    Vector<2> expect({1, 0});
    EXPECT_EQ(expect, actual);
  }
  // size:1x2 * 1
  {
    Vector<2> v({1});
    Matrix<2> m(1, 2);
    m(0, 0) = 1;
    m(0, 1) = 1;

    Vector<2> actual = m * v;

    Vector<2> expect({1});
    EXPECT_EQ(expect, actual);
  }
  // size:2x1 * 1
  {
    Vector<2> v({1});
    Matrix<2> m(2, 1);
    m(0, 0) = 1;
    m(1, 0) = 0;

    Vector<2> actual = m * v;

    Vector<2> expect({1, 0});
    EXPECT_EQ(expect, actual);
  }
}
} // namespace gns
