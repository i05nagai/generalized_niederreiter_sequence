#pragma once
#include <gtest/gtest.h>

#define GF_EXPECT_ARRAY_EQ(expect, actual, num)             \
    for (int i = 0; i < num; ++i) {                         \
      EXPECT_EQ(expect[i], actual[i]);                      \
    }                                                       

#define GF_EXPECT_POLYNOMIAL_EQ(expect, actual)             \
    EXPECT_EQ((expect).toString(), (actual).toString());
