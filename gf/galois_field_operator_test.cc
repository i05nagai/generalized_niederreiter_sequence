#include "gf/galois_field_operator.h"
#include <gtest/gtest.h>

namespace gf {
  TEST(operator_test, add_test)
  {
    // 0 + 0
    {
      const unsigned char l = 0;
      const unsigned char r = 0;
      const unsigned char result = add<2>(l, r);
      EXPECT_EQ(0, result);
    }
    // 0 + 1
    {
      const unsigned char l = 0;
      const unsigned char r = 1;
      const unsigned char result = add<2>(l, r);
      EXPECT_EQ(1, result);
    }
    // 1 + 0
    {
      const unsigned char l = 1;
      const unsigned char r = 0;
      const unsigned char result = add<2>(l, r);
      EXPECT_EQ(1, result);
    }
    // 1 + 1
    {
      const unsigned char l = 1;
      const unsigned char r = 1;
      const unsigned char result = add<2>(l, r);
      EXPECT_EQ(0, result);
    }
  }

  TEST(operator_test, sub_test)
  {
    // 0 - 0
    {
      const unsigned char l = 0;
      const unsigned char r = 0;
      const unsigned char result = sub<2>(l, r);
      EXPECT_EQ(0, result);
    }
    // 0 - 1
    {
      const unsigned char l = 0;
      const unsigned char r = 1;
      const unsigned char result = sub<2>(l, r);
      EXPECT_EQ(1, result);
    }
    // 1 - 0
    {
      const unsigned char l = 1;
      const unsigned char r = 0;
      const unsigned char result = sub<2>(l, r);
      EXPECT_EQ(1, result);
    }
    // 1 - 1
    {
      const unsigned char l = 1;
      const unsigned char r = 1;
      const unsigned char result = sub<2>(l, r);
      EXPECT_EQ(0, result);
    }
  }

  TEST(operator_test, mult_test)
  {
    // 0 * 0
    {
      const unsigned char l = 0;
      const unsigned char r = 0;
      const unsigned char result = mult<2>(l, r);
      EXPECT_EQ(0, result);
    }
    // 0 * 1
    {
      const unsigned char l = 0;
      const unsigned char r = 1;
      const unsigned char result = mult<2>(l, r);
      EXPECT_EQ(0, result);
    }
    // 1 * 0
    {
      const unsigned char l = 1;
      const unsigned char r = 0;
      const unsigned char result = mult<2>(l, r);
      EXPECT_EQ(0, result);
    }
    // 1 * 1
    {
      const unsigned char l = 1;
      const unsigned char r = 1;
      const unsigned char result = mult<2>(l, r);
      EXPECT_EQ(1, result);
    }
  }

  TEST(operator_test, div_test)
  {
    // 0 / 1
    {
      const unsigned char l = 0;
      const unsigned char r = 1;
      const unsigned char result = div<2>(l, r);
      EXPECT_EQ(0, result);
    }
    // 1 / 1
    {
      const unsigned char l = 1;
      const unsigned char r = 1;
      const unsigned char result = div<2>(l, r);
      EXPECT_EQ(1, result);
    }
  }
} // namespace gf
