#include <gtest/gtest.h>
#include "gns/laurent_series.h"
#include "gns/test_util/gtest_assertion.h"
#include "gns/test_util/gtest_helper_macro.h"
#include "gns/test_util/test_data.h"

namespace gns {
TEST(laurent_series_test, LaurentSeriesDivisionFirstEquations)
{
  // TODO
}

TEST(laurent_series_test, LaurentSeriesDivisionSecondEquations)
{
  // TODO
}

TEST(laurent_series_test, LaurentSeriesDivisionLastEquations)
{
  // TODO
}

TEST(laurent_series_test, SolveLaurentSeriesDivision) {
  // deg(a) = 0, deg(b) = 1
  {
    // 1
    GaloisFieldPolynomial<2> a({1});
    // x + 1
    GaloisFieldPolynomial<2> b({0, 1});
    const size_t max_degree = 32;

    // 1 / x
    std::unique_ptr<GaloisField<2>[]> actual =
        SolveLaurentSeriesDivision<2>(a, b, max_degree);

    std::unique_ptr<GaloisField<2>[]> expect =
        test_util::MakeGaloisFieldArray<2>({
            // clang-format off
        0, 1, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0
            // clang-format on
        });
    for (size_t i = 0; i < max_degree + 1; ++i) {
      GNS_EXPECT_EQ_WITH_INDEX(expect[i], actual[i], i);
    }
  }
  // deg(a) = 1, deg(b) = 2
  {
    // x
    GaloisFieldPolynomial<2> a({0, 1});
    // x + 1
    GaloisFieldPolynomial<2> b({0, 1, 1});
    const size_t max_degree = 32;

    // x / (x + 1)
    std::unique_ptr<GaloisField<2>[]> actual =
        SolveLaurentSeriesDivision<2>(a, b, max_degree);

    std::unique_ptr<GaloisField<2>[]> expect =
        test_util::MakeGaloisFieldArray<2>({
            // clang-format off
        0, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1
            // clang-format on
        });
    for (size_t i = 0; i < max_degree + 1; ++i) {
      GNS_EXPECT_EQ_WITH_INDEX(expect[i], actual[i], i);
    }
  }
  {
    // to divide by 3
    const size_t max_degree = 32;
    // x
    GaloisFieldPolynomial<2> numerator({0, 1});
    // x^{2} + x + 1
    GaloisFieldPolynomial<2> denominator({1, 1, 1});
    std::unique_ptr<GaloisField<2>[]> actual =
        SolveLaurentSeriesDivision<2>(numerator, denominator, max_degree);

    // x / (x^{2} + x + 1) = \sum_{j=0}^{\infty}(x^{-3j + 1} + x^{-3j+2})
    std::unique_ptr<GaloisField<2>[]> expect =
        test_util::MakeGaloisFieldArray<2>({
            // clang-format off
        0, 1, 1, 0, 1, 1,
        0, 1, 1, 0, 1, 1,
        0, 1, 1, 0, 1, 1,
        0, 1, 1, 0, 1, 1,
        0, 1, 1, 0, 1, 1,
        0, 1, 1,
            // clang-format on
        });
    for (size_t i = 0; i < max_degree + 1; ++i) {
      GNS_EXPECT_EQ_WITH_INDEX(expect[i], actual[i], i);
    }
  }
  // deg(a) = 4, deg(b) = 10
  {
    const size_t dividend_degree = 4;
    GaloisFieldPolynomial<2> a =
        test_util::TestData::GetRandomPolynomial<2>(dividend_degree);
    const size_t divisor_degree = 10;
    GaloisFieldPolynomial<2> b =
        test_util::TestData::GetRandomPolynomial<2>(divisor_degree);
    const size_t max_degree = 32;

    std::unique_ptr<GaloisField<2>[]> c =
        SolveLaurentSeriesDivision<2>(a, b, max_degree);

    // check a = b * c
    const int n = dividend_degree;
    const int m = divisor_degree;
    for (int i = -n; i <= 0; ++i) {
      GaloisField<2> sum = 0;
      for (int j = 0; j < m + i; ++j) {
        sum = sum + b[m - j] * c[-(-i - (m - j))];
      }
      GNS_EXPECT_EQ_WITH_INDEX(a[-i], sum, -i);
    }
  }
}
} // namespace gns
