#include "gf/IrreduciblePolynomial.h"
#include "gf/gtest_helper_macro.h"
#include <gtest/gtest.h>

namespace gf {
  TEST(IrreduciblePolynomialTest, operatorParenthesisTest)
  {
    std::vector<Polynomial<2>> expects = {
#include "irreducible_polynomial.txt"
    };
    const size_t num = expects.size();
    IrreduciblePolynomialGenerator<2> generator;
    std::vector<Polynomial<2>> actual = generator(num);
    for (size_t i = 0; i < num; ++i) {
      GF_EXPECT_POLYNOMIAL_EQ(expects[i], actual[i]);
    }
  }
} // namespace gf

