#pragma once
#include <gtest/gtest.h>
#include <functional>
#include <type_traits>

#define GNS_EXPECT_ARRAY_EQ(expect, actual, num) \
  for (decltype(num) i = 0; i < num; ++i) {      \
    EXPECT_EQ(expect[i], actual[i]);             \
  }

#define GSN_EXPECT_POLYNOMIAL_EQ(expect, actual) \
  EXPECT_EQ(expect.degree(), actual.degree());   \
  EXPECT_EQ((expect), (actual));

#define GNS_EXPECT_VECTOR_EQ(expect, actual, type)  \
  do {                                              \
    EXPECT_EQ(expect.size(), actual.size());        \
    for (size_t i = 0; i < expect.size(); ++i) {    \
      const auto& e = static_cast<type>(expect[i]); \
      const auto& a = static_cast<type>(actual[i]); \
      EXPECT_EQ(e, a);                              \
    }                                               \
  } while (false);
