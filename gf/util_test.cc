#include "gf/util.h"
#include "gf/gtest_helper_macro.h"
#include <gtest/gtest.h>

namespace gf {
  TEST(util_test, calcBaseAdic)
  {
    // Base = 2
    {
      std::pair<size_t, std::unique_ptr<unsigned char[]>> result
        = calcBaseAdic<2>(1);
      const std::unique_ptr<unsigned char[]>& expect = result.second;
      size_t size = result.first;
      unsigned char actual[] = {1};

      GF_EXPECT_ARRAY_EQ(expect, actual, size);
    }
    {
      std::pair<size_t, std::unique_ptr<unsigned char[]>> result
        = calcBaseAdic<2>(2);
      const std::unique_ptr<unsigned char[]>& expect = result.second;
      size_t size = result.first;
      unsigned char actual[2] = {0, 1};

      GF_EXPECT_ARRAY_EQ(expect, actual, size);
    }
    {
      std::pair<size_t, std::unique_ptr<unsigned char[]>> result
        = calcBaseAdic<2>(4);
      const std::unique_ptr<unsigned char[]>& expect = result.second;
      size_t size = result.first;
      unsigned char actual[3] = {0, 0, 1};

      GF_EXPECT_ARRAY_EQ(expect, actual, size);
    }
    {
      std::pair<size_t, std::unique_ptr<unsigned char[]>> result
        = calcBaseAdic<2>(9);
      const std::unique_ptr<unsigned char[]>& expect = result.second;
      size_t size = result.first;
      unsigned char actual[4] = {1, 0, 0, 1};

      GF_EXPECT_ARRAY_EQ(expect, actual, size);
    }
  }
} // namespace gf
