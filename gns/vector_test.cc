#include "gns/vector.h"
#include <gtest/gtest.h>

namespace gns {
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
