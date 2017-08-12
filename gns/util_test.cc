#include "gns/test_util/gtest_helper_macro.h"
#include "gns/util.h"
#include <gtest/gtest.h>

namespace gns {
TEST(util_test, CalculateBaseAdic)
{
  // Base = 2
  {
    std::pair<size_t, std::unique_ptr<GaloisField<2>[]>> result
      = CalculateBaseAdic<2>(1);
    const std::unique_ptr<GaloisField<2>[]>& expect = result.second;
    size_t size = result.first;
    unsigned char actual[] = {1};

    GNS_EXPECT_ARRAY_EQ(expect, actual, size);
  }
  {
    std::pair<size_t, std::unique_ptr<GaloisField<2>[]>> result
      = CalculateBaseAdic<2>(2);
    const std::unique_ptr<GaloisField<2>[]>& expect = result.second;
    size_t size = result.first;
    unsigned char actual[] = {0, 1};

    GNS_EXPECT_ARRAY_EQ(expect, actual, size);
  }
  {
    std::pair<size_t, std::unique_ptr<GaloisField<2>[]>> result
      = CalculateBaseAdic<2>(4);
    const std::unique_ptr<GaloisField<2>[]>& expect = result.second;
    size_t size = result.first;
    unsigned char actual[3] = {0, 0, 1};

    GNS_EXPECT_ARRAY_EQ(expect, actual, size);
  }
  {
    std::pair<size_t, std::unique_ptr<GaloisField<2>[]>> result
      = CalculateBaseAdic<2>(9);
    const std::unique_ptr<GaloisField<2>[]>& expect = result.second;
    size_t size = result.first;
    unsigned char actual[4] = {1, 0, 0, 1};

    GNS_EXPECT_ARRAY_EQ(expect, actual, size);
  }
}
} // namespace gns
