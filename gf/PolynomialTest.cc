#include "gf/Polynomial.h"
#include "gf/gtest_helper_macro.h"
#include <gtest/gtest.h>
#include <string>

namespace gf {
  TEST(PolynomialTest, constructorTest)
  {
    Polynomial<2> p(0);
    EXPECT_EQ(0, p[0]);
  }

  TEST(PolynomialTest, copyConstructorTest)
  {
    Polynomial<2> p1({0, 0, 1});
    Polynomial<2> p(p1);
    EXPECT_EQ(p1.toString(), p.toString());
  }

  TEST(PolynomialTest, toStringTest)
  {
    // INTEGER
    {
      Polynomial<2> p({0});
      const std::string actual = p.toString(
          EnumPolynomialExpression::INTEGER);
      EXPECT_EQ("0", actual);
    }
    {
      Polynomial<2> p({1, 1});
      const std::string actual = p.toString(
          EnumPolynomialExpression::INTEGER);
      EXPECT_EQ("3", actual);
    }
    {
      Polynomial<2> p({1, 0, 0, 1});
      const std::string actual = p.toString(
          EnumPolynomialExpression::INTEGER);
      EXPECT_EQ("9", actual);
    }
    // COEFFICIENTS
    {
      Polynomial<2> p(0);
      const std::string actual = p.toString(
          EnumPolynomialExpression::COEFFICIENTS);
      EXPECT_EQ("0", actual);
    }
    {
      Polynomial<2> p({1, 1});
      const std::string actual = p.toString(
          EnumPolynomialExpression::COEFFICIENTS);
      EXPECT_EQ("1  1", actual);
    }
    {
      Polynomial<2> p({1, 0, 0, 1});
      const std::string actual = p.toString(
          EnumPolynomialExpression::COEFFICIENTS);
      EXPECT_EQ("1  0  0  1", actual);
    }
    // POLYNOMIAL
    {
      Polynomial<2> p(0);
      const std::string actual = p.toString(
          EnumPolynomialExpression::POLYNOMIAL);
      EXPECT_EQ("0", actual);
    }
    {
      Polynomial<2> p({1, 1});
      const std::string actual = p.toString(
          EnumPolynomialExpression::POLYNOMIAL);
      EXPECT_EQ("1X^{1} + 1", actual);
    }
    {
      Polynomial<2> p({1, 0, 0, 1});
      const std::string actual = p.toString(
          EnumPolynomialExpression::POLYNOMIAL);
      EXPECT_EQ("1X^{3} + 0X^{2} + 0X^{1} + 1", actual);
    }
  }

  TEST(PolynomialTest, operatorPlusTest)
  {
    // 0
    {
      Polynomial<2> p1({1});
      Polynomial<2> p2({0});
      p1 += p2;

      Polynomial<2> expect({1});
      EXPECT_EQ(expect.toString(), p1.toString());
    }
    // 1
    {
      Polynomial<2> p1({1, 1, 0, 1});
      Polynomial<2> p2({1});
      p1 += p2;

      Polynomial<2> expect({0, 1, 0, 1});
      EXPECT_EQ(expect.toString(), p1.toString());
    }
    // 1
    {
      Polynomial<2> p1({1, 1, 0, 1});
      Polynomial<2> p2({1});
      p2 += p1;

      Polynomial<2> expect({0, 1, 0, 1});
      EXPECT_EQ(expect.toString(), p2.toString());
    }
    // delete coefficient of highest degree
    {
      Polynomial<2> p1({1, 1, 0, 1});
      Polynomial<2> p2({0, 0, 0, 1});
      p1 += p2;

      Polynomial<2> expect({1, 1});
      EXPECT_EQ(expect.toString(), p1.toString());
    }
    // poly
    {
      // X^{3} + X^{1} + 1
      Polynomial<2> p1({1, 1, 0, 1});
      // X^{2} + 1
      Polynomial<2> p2({1, 0, 1});
      p1 += p2;

      // X^{3} + X^{1} + 1
      // X^{2} + 1
      Polynomial<2> expect({0, 1, 1, 1});
      EXPECT_EQ(expect.toString(), p1.toString());
    }
    // poly
    {
      // X^{3} + X^{1} + 1
      Polynomial<2> p1({1, 1, 0, 1});
      // X^{2} + 1
      Polynomial<2> p2({1, 0, 1});
      p2 += p1;

      // X^{3} + X^{1} + 1
      // X^{2} + 1
      Polynomial<2> expect({0, 1, 1, 1});
      EXPECT_EQ(expect.toString(), p2.toString());
    }
  }

  TEST(PolynomialTest, operatorMinusTest)
  {
    // 0
    {
      Polynomial<2> p1({1});
      Polynomial<2> p2({0});
      p1 -= p2;

      Polynomial<2> expect({1});
      EXPECT_EQ(expect.toString(), p1.toString());
    }
    // 1
    {
      Polynomial<2> p1({1, 1, 0, 1});
      Polynomial<2> p2({1});
      p1 -= p2;

      Polynomial<2> expect({0, 1, 0, 1});
      EXPECT_EQ(expect.toString(), p1.toString());
    }
    // 1
    {
      Polynomial<2> p1({1, 1, 0, 1});
      Polynomial<2> p2({1});
      p2 -= p1;

      Polynomial<2> expect({0, 1, 0, 1});
      EXPECT_EQ(expect.toString(), p2.toString());
    }
    // delete coefficient of highest degree
    {
      Polynomial<2> p1({1, 1, 0, 1});
      Polynomial<2> p2({0, 0, 0, 1});
      p1 -= p2;

      Polynomial<2> expect({1, 1});
      EXPECT_EQ(expect.toString(), p1.toString());
    }
    // poly
    {
      // X^{3} + X^{1} + 1
      Polynomial<2> p1({1, 1, 0, 1});
      // X^{2} + 1
      Polynomial<2> p2({1, 0, 1});
      p1 -= p2;

      // X^{3} + X^{1} + 1
      // X^{2} + 1
      Polynomial<2> expect({0, 1, 1, 1});
      EXPECT_EQ(expect.toString(), p1.toString());
    }
    // poly
    {
      // X^{3} + X^{1} + 1
      Polynomial<2> p1({1, 1, 0, 1});
      // X^{2} + 1
      Polynomial<2> p2({1, 0, 1});
      p2 -= p1;

      // X^{3} + X^{1} + 1
      // X^{2} + 1
      Polynomial<2> expect({0, 1, 1, 1});
      EXPECT_EQ(expect.toString(), p2.toString());
    }
  }

  TEST(PolynomialTest, operatorMultiplyTest)
  {
    // 0
    {
      Polynomial<2> p1({1});
      Polynomial<2> p2(0);
      p1 *= p2;
      EXPECT_EQ(true, p1.isZero());
    }
    // 1: identity in polynominal
    {
      Polynomial<2> expect({1, 1, 0, 1});
      Polynomial<2> p1({1, 1, 0, 1});
      Polynomial<2> p2({1});
      p1 *= p2;
      EXPECT_EQ(expect, p1);
    }
    // poly
    {
      // X^{3} + X^{1} + 1
      Polynomial<2> p1({1, 1, 0, 1});
      // X^{2} + 1
      Polynomial<2> p2({1, 0, 1});
      p1 *= p2;

      // X^{3} + X^{1} + 1
      // X^{5} + X^{3} + X^{2}
      Polynomial<2> expect({1, 1, 1, 0, 0, 1});
      EXPECT_EQ(expect, p1);
    }
  }

  TEST(PolynomialTest, isZeroTest)
  {
    // constant
    {
      Polynomial<2> p({1});
      EXPECT_FALSE(p.isZero());
      
    }
    // poly
    {
      Polynomial<2> p({1, 1});
      EXPECT_FALSE(p.isZero());
    }
    // 0
    {
      Polynomial<2> p({0});
      EXPECT_TRUE(p.isZero());
    }
  }

  TEST(PolynomialTest, resizeTest)
  {
    // shrink
    {
      Polynomial<2> p({1, 1, 1, 1});
      p.resize(2);
      
      Polynomial<2> expect({1, 1, 1});
      EXPECT_EQ(expect, p);
    }
    // expand
    {
      Polynomial<2> p({1});
      p.resize(3);
      
      Polynomial<2> expect({1, 0, 0, 0});
      EXPECT_EQ(expect, p);
    }
    // 0
    {
      Polynomial<2> p({0});
      p.resize(3);

      Polynomial<2> expect({0, 0, 0, 0});
      EXPECT_EQ(expect.toString(), p.toString());
    }
  }

  /*--------------------------------------------------------------------------
   * free funcitions
   *------------------------------------------------------------------------*/
  TEST(PolynomialTest, euclidean_divisionTest)
  {
    // divide by consntant
    {
      Polynomial<2> dividend({1});
      Polynomial<2> divisor({1});
      std::pair<Polynomial<2>, Polynomial<2>> result 
        = gf::euclidean_division<2>(dividend, divisor);
      const Polynomial<2> quotient = result.first;
      const Polynomial<2> residual = result.second;
      // 1 / 1
      Polynomial<2> expectQuotient({1});
      Polynomial<2> expectResidual({0});
      GF_EXPECT_POLYNOMIAL_EQ(expectQuotient, quotient);
      GF_EXPECT_POLYNOMIAL_EQ(expectResidual, residual);
    }
    // expand
    {
      // X^{3} + X^{2} + X^{1} + 1
      Polynomial<2> dividend({1, 1, 1, 1});
      // X^{3} + X^{2} + X^{1} + 1
      Polynomial<2> divisor({1, 1, 1, 1});
      std::pair<Polynomial<2>, Polynomial<2>> result 
        = gf::euclidean_division<2>(dividend, divisor);
      const Polynomial<2> quotient = result.first;
      const Polynomial<2> residual = result.second;
      // dividend / divisor = 1
      Polynomial<2> expectQuotient({1});
      Polynomial<2> expectResidual({0});
      GF_EXPECT_POLYNOMIAL_EQ(expectQuotient, quotient);
      GF_EXPECT_POLYNOMIAL_EQ(expectResidual, residual);
    }
    {
      // X^{3} + X^{2} + X^{1} + 1
      Polynomial<2> dividend({1, 1, 1, 1});
      // X^{2} + X^{1} + 1
      Polynomial<2> divisor({1, 1, 1});
      std::pair<Polynomial<2>, Polynomial<2>> result 
        = gf::euclidean_division<2>(dividend, divisor);
      const Polynomial<2> quotient = result.first;
      const Polynomial<2> residual = result.second;

      // X^{1}(X^{2} + X^{1} + 1)
      // = X^{3} + X^{2} + X^{1}
      Polynomial<2> expectQuotient({0, 1});
      Polynomial<2> expectResidual({1});
      GF_EXPECT_POLYNOMIAL_EQ(expectQuotient, quotient);
      GF_EXPECT_POLYNOMIAL_EQ(expectResidual, residual);
    }
    {
      // X^{2} + X^{1} + 1
      Polynomial<2> dividend({1, 1, 1});
      // X^{1}
      Polynomial<2> divisor({0, 1});
      std::pair<Polynomial<2>, Polynomial<2>> result 
        = gf::euclidean_division<2>(dividend, divisor);
      const Polynomial<2> quotient = result.first;
      const Polynomial<2> residual = result.second;

      // X^{1}(X^{1} + 1) + 1
      Polynomial<2> expectQuotient({1, 1});
      Polynomial<2> expectResidual({1});
      GF_EXPECT_POLYNOMIAL_EQ(expectQuotient, quotient);
      GF_EXPECT_POLYNOMIAL_EQ(expectResidual, residual);
    }
  }
  TEST(PolynomialTest, toPolynomialTest)
  {
    std::vector<std::string> data = {
      {"1"},
      {"2"},
      {"4"},
    };
    std::vector<Polynomial<2>> expects = {
      {1},
      {0, 1},
      {0, 0, 1},
    };
    const size_t num = expects.size();
    for (size_t i = 0; i < num; ++i) {
      const Polynomial<2> actual = toPolynomial<2>(data[i].c_str());
      GF_EXPECT_POLYNOMIAL_EQ(expects[i], actual);
    }
  }
} // namespace gf
