#include "gns/matrix.h"
#include <gtest/gtest.h>

namespace gns {
TEST(Matrix, ConstructorTest) {
  const size_t size = 2;
  std::unique_ptr<GaloisField<2>[]> data(new GaloisField<2>[size * size]);
  data[0 + 0] = 1;
  data[0 + 1] = 1;
  data[2 + 0] = 1;
  data[2 + 1] = 1;
  Matrix<2> m(size, size, std::move(data));

  EXPECT_EQ(GaloisField<2>(1), m(0, 0));
  EXPECT_EQ(GaloisField<2>(1), m(0, 1));
  EXPECT_EQ(GaloisField<2>(1), m(1, 0));
  EXPECT_EQ(GaloisField<2>(1), m(1, 1));
}

TEST(Matrix, RowSizeTest) {
  {
    const size_t expect = 0;
    const size_t col_size = 0;
    Matrix<2> m(expect, col_size);
    EXPECT_EQ(expect, m.RowSize());
  }
  {
    const size_t expect = 2;
    const size_t col_size = 0;
    Matrix<2> m(expect, col_size);
    EXPECT_EQ(expect, m.RowSize());
  }
}

TEST(Matrix, ColSizeTest) {
  {
    const size_t row_size = 0;
    const size_t expect = 0;
    Matrix<2> m(row_size, expect);
    EXPECT_EQ(expect, m.ColSize());
  }
  {
    const size_t row_size = 0;
    const size_t expect = 2;
    Matrix<2> m(row_size, expect);
    EXPECT_EQ(expect, m.ColSize());
  }
}

TEST(Matrix, OperatorParenthesisTest) {
  Matrix<2> m(1, 1);
  m(0, 0) = 1;
  GaloisField<2> expect = 1;
  EXPECT_EQ(expect, m(0, 0));
}

}  // namespace gns
