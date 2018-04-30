#include "gns/matrix_func.h"
#include <gtest/gtest.h>

namespace gns {
template <typename T>
class TypedTest : public testing::Test {};
typedef ::testing::Types<Matrix<2>, Matrix<4>> IsIdentityTestType;
TYPED_TEST_CASE(TypedTest, IsIdentityTestType);
TYPED_TEST(TypedTest, IsIdentity) {
  // not identity
  {
    TypeParam m(2, 2);
    m(0, 0) = 1;
    m(0, 1) = 1;
    m(1, 0) = 0;
    m(1, 1) = 1;

    EXPECT_FALSE(IsIdentity(m));
  }
  // identity
  {
    TypeParam m(2, 2);
    m(0, 0) = 1;
    m(0, 1) = 0;
    m(1, 0) = 0;
    m(1, 1) = 1;

    EXPECT_TRUE(IsIdentity(m));
  }
}
}  // namespace gns
