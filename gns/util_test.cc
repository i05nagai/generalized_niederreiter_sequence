#include "gns/test_util/gtest_assertion.h"
#include "gns/test_util/gtest_helper_macro.h"
#include "gns/util.h"
#include <gtest/gtest.h>

namespace gns {
TEST(util_test, CalculateBaseAdic2) {
  // Base = 2
  {
    std::pair<size_t, std::unique_ptr<GaloisField<2>[]>> result =
        CalculateBaseAdic<2>(1);
    const std::unique_ptr<GaloisField<2>[]>& expect = result.second;
    size_t size = result.first;
    unsigned char actual[] = {1};

    GNS_EXPECT_ARRAY_EQ(expect, actual, size);
  }
  {
    std::pair<size_t, std::unique_ptr<GaloisField<2>[]>> result =
        CalculateBaseAdic<2>(2);
    const std::unique_ptr<GaloisField<2>[]>& expect = result.second;
    size_t size = result.first;
    unsigned char actual[] = {0, 1};

    GNS_EXPECT_ARRAY_EQ(expect, actual, size);
  }
  {
    std::pair<size_t, std::unique_ptr<GaloisField<2>[]>> result =
        CalculateBaseAdic<2>(4);
    const std::unique_ptr<GaloisField<2>[]>& expect = result.second;
    size_t size = result.first;
    unsigned char actual[3] = {0, 0, 1};

    GNS_EXPECT_ARRAY_EQ(expect, actual, size);
  }
  {
    std::pair<size_t, std::unique_ptr<GaloisField<2>[]>> result =
        CalculateBaseAdic<2>(9);
    const std::unique_ptr<GaloisField<2>[]>& expect = result.second;
    size_t size = result.first;
    unsigned char actual[4] = {1, 0, 0, 1};

    GNS_EXPECT_ARRAY_EQ(expect, actual, size);
  }
}

TEST(util_test, CalculateBaseAdic4) {
  constexpr int Base = 4;
  // Base = 4
  {
    std::pair<size_t, std::unique_ptr<GaloisField<Base>[]>> result =
        CalculateBaseAdic<Base>(1);
    const std::unique_ptr<GaloisField<Base>[]>& expect = result.second;
    size_t size = result.first;
    unsigned char actual[] = {1};

    GNS_EXPECT_ARRAY_EQ(expect, actual, size);
  }
  {
    std::pair<size_t, std::unique_ptr<GaloisField<Base>[]>> result =
        CalculateBaseAdic<Base>(4);
    const std::unique_ptr<GaloisField<Base>[]>& expect = result.second;
    size_t size = result.first;
    unsigned char actual[2] = {0, 1};

    GNS_EXPECT_ARRAY_EQ(expect, actual, size);
  }
  {
    std::pair<size_t, std::unique_ptr<GaloisField<Base>[]>> result =
        CalculateBaseAdic<Base>(17);
    const std::unique_ptr<GaloisField<Base>[]>& expect = result.second;
    size_t size = result.first;
    unsigned char actual[3] = {1, 0, 1};

    GNS_EXPECT_ARRAY_EQ(expect, actual, size);
  }
}

TEST(util_test, BaseAdicToDouble2) {
  {
    Vector<2> v({1});
    const double actual = BaseAdicToDouble(v);
    EXPECT_DOUBLE_EQ(0.5, actual);
  }
  {
    Vector<2> v({0, 1});
    const double actual = BaseAdicToDouble(v);
    EXPECT_DOUBLE_EQ(0.25, actual);
  }
}

TEST(util_test, BaseAdicToDouble4) {
  {
    Vector<4> v({1});
    const double actual = BaseAdicToDouble(v);
    EXPECT_DOUBLE_EQ(0.25, actual);
  }
  {
    Vector<4> v({0, 1});
    const double actual = BaseAdicToDouble(v);
    EXPECT_DOUBLE_EQ(0.25 * 0.25, actual);
  }
}

TEST(util_test, FindCarryBitBase2) {
  std::vector<size_t> data = {
    0, 1,
  };
  std::vector<size_t> expects = {
    1, 1,
  };
  for (size_t i = 0; i < data.size(); ++i) {
    const size_t actual = FindCarryBit<2>(data[i]);
    const size_t expect = expects[i];
    GNS_EXPECT_EQ_WITH_INDEX(expect, actual, i);
  }
}

TEST(util_test, FindCarryBitBase4) {
  std::vector<size_t> data = {
    0, // 00
    1, // 01
    2, // 10
    3, // 11
  };
  std::vector<size_t> expects = {
    3,
    1,
    3,
    1,
  };
  for (size_t i = 0; i < data.size(); ++i) {
    const size_t actual = FindCarryBit<4>(data[i]);
    const size_t expect = expects[i];
    GNS_EXPECT_EQ_WITH_INDEX(expect, actual, i);
  }
}

TEST(util_test, FindCarryBitBase16) {
  std::vector<size_t> data = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
  };
  std::vector<size_t> expects = {
    15, // 1  = 0000
    1,  // 2  = 0001
    3,  // 3  = 0010
    1,  // 4  = 0011
    7,  // 5  = 0100
    1,  // 6  = 0101
    3,  // 7  = 0110
    1,  // 8  = 0111
    15, // 9  = 1000
    1,  // 10 = 1001
    3,  // 11 = 1010
    1,  // 12 = 1011
    7,  // 13 = 1100
    1,  // 14 = 1101
    3,  // 15 = 1110
    1, // 16 = 1111
  };
  for (size_t i = 0; i < data.size(); ++i) {
    const size_t actual = FindCarryBit<16>(data[i]);
    const size_t expect = expects[i];
    GNS_EXPECT_EQ_WITH_INDEX(expect, actual, i);
  }
}
}  // namespace gns
