#include "gns/util.h"
#include <gtest/gtest.h>
#include "gns/test_util/gtest_helper_macro.h"

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
}  // namespace gns
