#include "gf/IrreduciblePolynomial.h"
#include "gf/gtest_helper_macro.h"
#include <gtest/gtest.h>
#include <sstream>

namespace gf {
  TEST(IrreduciblePolynomialTest, constructorTest)
  {
    std::string expect("2\n4\n");
    std::istringstream inputStream(expect);
    IrreduciblePolynomialGenerator<2> generator(inputStream);

    std::stringstream stringStream;
    generator.save(stringStream);
    
    ASSERT_EQ(expect, stringStream.str());
  }

  TEST(IrreduciblePolynomialTest, operatorParenthesisTest)
  {
    std::vector<Polynomial<2>> expects = {
#include "irreducible_polynomial_test.txt"
    };
    const size_t num = expects.size();
    IrreduciblePolynomialGenerator<2> generator;
    std::vector<Polynomial<2>> actual = generator(num);
    for (size_t i = 0; i < num; ++i) {
      GF_EXPECT_POLYNOMIAL_EQ(expects[i], actual[i]);
    }
  }

  TEST(IrreduciblePolynomialTest, getNextTest)
  {
    std::vector<Polynomial<2>> expects = {
#include "irreducible_polynomial_test.txt"
    };
    const size_t num = expects.size();
    IrreduciblePolynomialGenerator<2> generator;
    for (size_t i = 0; i < num; ++i) {
      const Polynomial<2>& actual = generator.getNext();
      GF_EXPECT_POLYNOMIAL_EQ(expects[i], actual);
    }
  }
} // namespace gf

