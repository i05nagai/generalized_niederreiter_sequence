#include "gns/irreducible_polynomial.h"
#include <gtest/gtest.h>
#include <sstream>
#include "gns/test_util/gtest_helper_macro.h"

namespace gns {
/*--------------------------------------------------------------------------
 * Base 2
 *------------------------------------------------------------------------*/
TEST(irreducible_polynomial_test, IrreduciblePolynomialGetNextBase2Test0) {
  IrreduciblePolynomialGenerator<2> generator;
  GaloisFieldPolynomial<2> actual = generator.GetNext();

  GaloisFieldPolynomial<2> expect({0, 1});
  GSN_EXPECT_POLYNOMIAL_EQ(expect, actual);
}

TEST(irreducible_polynomial_test, IrreduciblePolynomialGetNextBase2Test1) {
  std::vector<GaloisFieldPolynomial<2>> expects = {
      // clang-format off
    {0, 1},
    {1, 1},
    {1, 1, 1},
    {1, 1, 0, 1},
    {1, 0, 1, 1},
    {1, 1, 0, 0, 1},
    {1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1},
      // clang-format on
  };
  const size_t num = expects.size();
  IrreduciblePolynomialGenerator<2> generator;
  for (size_t i = 0; i < num; ++i) {
    const GaloisFieldPolynomial<2>& actual = generator.GetNext();
    EXPECT_EQ(expects[i], actual);
  }
}

TEST(irreducible_polynomial_test, IrreduciblePolynomialConstructorTest) {
  std::string expect("2\n4\n");
  std::istringstream input_stream(expect);
  IrreduciblePolynomialGenerator<2> generator(input_stream);

  std::stringstream string_stream;
  generator.Save(string_stream);

  EXPECT_EQ(expect, string_stream.str());
}

TEST(IrreduciblePolynomial, OperatorParenthesisTest) {
  std::vector<GaloisFieldPolynomial<2>> expects = {
      // clang-format off
    {0, 1},
    {1, 1},
    {1, 1, 1},
    {1, 1, 0, 1},
    {1, 0, 1, 1},
    {1, 1, 0, 0, 1},
    {1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 0, 1},
    {1, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1},
    {1, 0, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1},
      // clang-format on
  };
  const size_t num = expects.size();
  IrreduciblePolynomialGenerator<2> generator;
  std::vector<GaloisFieldPolynomial<2>> actual = generator(num);
  for (size_t i = 0; i < num; ++i) {
    EXPECT_EQ(expects[i], actual[i]);
  }
}
/*--------------------------------------------------------------------------
 * Base 4
 *------------------------------------------------------------------------*/
TEST(irreducible_polynomial_test, GetNext) {
  std::vector<GaloisFieldPolynomial<4>> expects = {
      // clang-format off
    {0, 1},
    {1, 1},
    {2, 1},
    {3, 1},
    {2, 1, 1},
    {3, 1, 1},
    {1, 2, 1},
    {2, 2, 1},
    {1, 3, 1},
    {3, 3, 1},
    {2, 0, 0, 1},
    {3, 0, 0, 1},
    {1, 1, 0, 1},
    {1, 2, 0, 1},
    {1, 3, 0, 1},
    {1, 0, 1, 1},
    {2, 1, 1, 1},
      // clang-format on
  };
  const size_t num = expects.size();
  IrreduciblePolynomialGenerator<4> generator;
  for (size_t i = 0; i < num; ++i) {
    const GaloisFieldPolynomial<4>& actual = generator.GetNext();
    EXPECT_EQ(expects[i], actual);
  }
}
}  // namespace gf
