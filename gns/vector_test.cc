#include "gns/vector.h"
#include <gtest/gtest.h>

namespace gns {
TEST(Vector, ConstructorTest) {
  {
    const size_t size = 2;
    std::unique_ptr<GaloisField<2>[]> data(new GaloisField<2>[size]);
    data[0] = 0;
    data[1] = 1;
    Vector<2> v(size, std::move(data));

    EXPECT_EQ(GaloisField<2>(0), v(0));
    EXPECT_EQ(GaloisField<2>(1), v(1));
  }
}

TEST(Vector, SizeTest) {
  {
    const size_t expect = 0;
    Vector<2> v(expect);
    EXPECT_EQ(expect, v.Size());
  }
  {
    const size_t expect = 2;
    Vector<2> v(expect);
    EXPECT_EQ(expect, v.Size());
  }
}

TEST(Vector, OperatorParenthesisTest) {
  Vector<2> v(1);
  v(0) = 1;
  GaloisField<2> expect = 1;
  EXPECT_EQ(expect, v(0));
}
}  // namespace gns
