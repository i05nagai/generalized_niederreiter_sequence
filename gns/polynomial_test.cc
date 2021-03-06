#include "gns/polynomial.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "gns/test_util/gtest_assertion.h"
#include "gns/test_util/gtest_helper_macro.h"
#include "gns/test_util/test_data.h"

namespace gns {
TEST(Polynomial, ConstructorTest) {
  GaloisFieldPolynomial<2> p(0);
  EXPECT_EQ(GaloisField<2>(0), p[0]);
}

TEST(Polynomial, CopyConstructorTest) {
  GaloisFieldPolynomial<2> p1({0, 0, 1});
  GaloisFieldPolynomial<2> p(p1);
  EXPECT_EQ(p, p1);
}

TEST(Polynomial, OperatorAssignTest) {
  GaloisFieldPolynomial<2> p1({0, 0, 1});
  GaloisFieldPolynomial<2> p = p1;
  EXPECT_EQ(p, p1);
}

TEST(Polynomial, OperatorPlusTest01) {
  // 1
  // 0
  GaloisFieldPolynomial<2> p1({1});
  GaloisFieldPolynomial<2> p2({0});
  p1 += p2;

  GaloisFieldPolynomial<2> expect({1});
  EXPECT_EQ(expect, p1);
}

TEST(Polynomial, OperatorPlusTest02) {
  // X^{3} + x^{1} + 1
  // 1
  GaloisFieldPolynomial<2> p1({1, 1, 0, 1});
  GaloisFieldPolynomial<2> p2({1});
  p1 += p2;

  GaloisFieldPolynomial<2> expect({0, 1, 0, 1});
  EXPECT_EQ(expect, p1);
}

TEST(Polynomial, OperatorPlusTest03) {
  // 1
  GaloisFieldPolynomial<2> p1({1, 1, 0, 1});
  GaloisFieldPolynomial<2> p2({1});
  p2 += p1;

  GaloisFieldPolynomial<2> expect({0, 1, 0, 1});
  EXPECT_EQ(expect, p2);
}

TEST(Polynomial, OperatorPlusTest04) {
  // delete coefficient of highest degree
  GaloisFieldPolynomial<2> p1({1, 1, 0, 1});
  GaloisFieldPolynomial<2> p2({0, 0, 0, 1});
  p1 += p2;

  GaloisFieldPolynomial<2> expect({1, 1});
  EXPECT_EQ(expect, p1);
}

TEST(Polynomial, OperatorPlusTest05) {
  // X^{3} + X^{1} + 1
  GaloisFieldPolynomial<2> p1({1, 1, 0, 1});
  // X^{2} + 1
  GaloisFieldPolynomial<2> p2({1, 0, 1});
  p1 += p2;

  // X^{3} + X^{1} + 1
  // X^{2} + 1
  GaloisFieldPolynomial<2> expect({0, 1, 1, 1});
  EXPECT_EQ(expect, p1);
}

TEST(Polynomial, OperatorPlusTest06) {
  // X^{3} + X^{1} + 1
  GaloisFieldPolynomial<2> p1({1, 1, 0, 1});
  // X^{2} + 1
  GaloisFieldPolynomial<2> p2({1, 0, 1});
  p2 += p1;

  // X^{3} + X^{1} + 1
  // X^{2} + 1
  GaloisFieldPolynomial<2> expect({0, 1, 1, 1});
  EXPECT_EQ(expect, p2);
}

TEST(PolynomialTest, OperatorSubTest) {
  // 0
  {
    GaloisFieldPolynomial<2> p1({1});
    GaloisFieldPolynomial<2> p2({0});
    p1 -= p2;

    GaloisFieldPolynomial<2> expect({1});
    EXPECT_EQ(expect, p1);
  }
  // 1
  {
    GaloisFieldPolynomial<2> p1({1, 1, 0, 1});
    GaloisFieldPolynomial<2> p2({1});
    p1 -= p2;

    GaloisFieldPolynomial<2> expect({0, 1, 0, 1});
    EXPECT_EQ(expect, p1);
  }
  // 1
  {
    GaloisFieldPolynomial<2> p1({1, 1, 0, 1});
    GaloisFieldPolynomial<2> p2({1});
    p2 -= p1;

    GaloisFieldPolynomial<2> expect({0, 1, 0, 1});
    EXPECT_EQ(expect, p2);
  }
  // delete coefficient of highest degree
  {
    GaloisFieldPolynomial<2> p1({1, 1, 0, 1});
    GaloisFieldPolynomial<2> p2({0, 0, 0, 1});
    p1 -= p2;

    GaloisFieldPolynomial<2> expect({1, 1});
    EXPECT_EQ(expect, p1);
  }
  // poly
  {
    // X^{3} + X^{1} + 1
    GaloisFieldPolynomial<2> p1({1, 1, 0, 1});
    // X^{2} + 1
    GaloisFieldPolynomial<2> p2({1, 0, 1});
    p1 -= p2;

    // X^{3} + X^{1} + 1
    // X^{2} + 1
    GaloisFieldPolynomial<2> expect({0, 1, 1, 1});
    EXPECT_EQ(expect, p1);
  }
  // poly
  {
    // X^{3} + X^{1} + 1
    GaloisFieldPolynomial<2> p1({1, 1, 0, 1});
    // X^{2} + 1
    GaloisFieldPolynomial<2> p2({1, 0, 1});
    p2 -= p1;

    // X^{3} + X^{1} + 1
    // X^{2} + 1
    GaloisFieldPolynomial<2> expect({0, 1, 1, 1});
    EXPECT_EQ(expect, p2);
  }
}

TEST(PolynomialTest, operatorMultiplyTest) {
  // 0
  {
    GaloisFieldPolynomial<2> p1({1});
    GaloisFieldPolynomial<2> p2(0);
    p1 *= p2;
    EXPECT_EQ(true, p1.IsZero());
  }
  // 1: identity in polynominal
  {
    GaloisFieldPolynomial<2> expect({1, 1, 0, 1});
    GaloisFieldPolynomial<2> p1({1, 1, 0, 1});
    GaloisFieldPolynomial<2> p2({1});
    p1 *= p2;
    EXPECT_EQ(expect, p1);
  }
  // poly
  {
    // X^{3} + X^{1} + 1
    GaloisFieldPolynomial<2> p1({1, 1, 0, 1});
    // X^{2} + 1
    GaloisFieldPolynomial<2> p2({1, 0, 1});
    p1 *= p2;

    // X^{3} + X^{1} + 1
    // X^{5} + X^{3} + X^{2}
    GaloisFieldPolynomial<2> expect({1, 1, 1, 0, 0, 1});
    EXPECT_EQ(expect, p1);
  }
}

TEST(PolynomialTest, IsZeroTest) {
  // constant
  {
    GaloisFieldPolynomial<2> p({1});
    EXPECT_FALSE(p.IsZero());
  }
  // poly
  {
    GaloisFieldPolynomial<2> p({1, 1});
    EXPECT_FALSE(p.IsZero());
  }
  // 0
  {
    GaloisFieldPolynomial<2> p({0});
    EXPECT_TRUE(p.IsZero());
  }
}

/*--------------------------------------------------------------------------
 * free function
 *------------------------------------------------------------------------*/

TEST(PolynomialTest, MakeBasePolynomial) {
  // constant
  {
    GaloisField<2> gf(1);
    GaloisFieldPolynomial<2> p = MakeBasePolynomial(0, gf);
    GaloisFieldPolynomial<2> expect({1});
    EXPECT_EQ(expect, p);
  }
  // 1
  {
    GaloisField<2> gf(1);
    GaloisFieldPolynomial<2> p = MakeBasePolynomial(1, gf);
    GaloisFieldPolynomial<2> expect({0, 1});
    EXPECT_EQ(expect, p);
  }
}

TEST(PolynomialTest, EuclidianDivisionTest) {
  // divide by 0
  {
    GaloisFieldPolynomial<2> dividend({0});
    GaloisFieldPolynomial<2> divisor({1});
    std::pair<GaloisFieldPolynomial<2>, GaloisFieldPolynomial<2>> result =
        EuclideanDivision<2>(dividend, divisor);
    const GaloisFieldPolynomial<2> quotient = result.first;
    const GaloisFieldPolynomial<2> residual = result.second;
    // 1 / 1
    GaloisFieldPolynomial<2> expect_quotient({0});
    GaloisFieldPolynomial<2> expect_residual({0});
    EXPECT_EQ(expect_quotient, quotient);
    EXPECT_EQ(expect_residual, residual);
  }
  // divide by consntant
  {
    GaloisFieldPolynomial<2> dividend({1});
    GaloisFieldPolynomial<2> divisor({1});
    std::pair<GaloisFieldPolynomial<2>, GaloisFieldPolynomial<2>> result =
        EuclideanDivision<2>(dividend, divisor);
    const GaloisFieldPolynomial<2> quotient = result.first;
    const GaloisFieldPolynomial<2> residual = result.second;
    // 1 / 1
    GaloisFieldPolynomial<2> expect_quotient({1});
    GaloisFieldPolynomial<2> expect_residual({0});
    EXPECT_EQ(expect_quotient, quotient);
    EXPECT_EQ(expect_residual, residual);
  }
  // expand
  {
    // X^{3} + X^{2} + X^{1} + 1
    GaloisFieldPolynomial<2> dividend({1, 1, 1, 1});
    // X^{3} + X^{2} + X^{1} + 1
    GaloisFieldPolynomial<2> divisor({1, 1, 1, 1});
    std::pair<GaloisFieldPolynomial<2>, GaloisFieldPolynomial<2>> result =
        EuclideanDivision<2>(dividend, divisor);
    const GaloisFieldPolynomial<2> quotient = result.first;
    const GaloisFieldPolynomial<2> residual = result.second;
    // dividend / divisor = 1
    GaloisFieldPolynomial<2> expect_quotient({1});
    GaloisFieldPolynomial<2> expect_residual({0});
    EXPECT_EQ(expect_quotient, quotient);
    EXPECT_EQ(expect_residual, residual);
  }
  {
    // X^{3} + X^{2} + X^{1} + 1
    GaloisFieldPolynomial<2> dividend({1, 1, 1, 1});
    // X^{2} + X^{1} + 1
    GaloisFieldPolynomial<2> divisor({1, 1, 1});
    std::pair<GaloisFieldPolynomial<2>, GaloisFieldPolynomial<2>> result =
        EuclideanDivision<2>(dividend, divisor);
    const GaloisFieldPolynomial<2> quotient = result.first;
    const GaloisFieldPolynomial<2> residual = result.second;

    // X^{1}(X^{2} + X^{1} + 1)
    // = X^{3} + X^{2} + X^{1}
    GaloisFieldPolynomial<2> expect_quotient({0, 1});
    GaloisFieldPolynomial<2> expect_residual({1});
    EXPECT_EQ(expect_quotient, quotient);
    EXPECT_EQ(expect_residual, residual);
  }
  {
    // X^{2} + X^{1} + 1
    GaloisFieldPolynomial<2> dividend({1, 1, 1});
    // X^{1}
    GaloisFieldPolynomial<2> divisor({0, 1});
    std::pair<GaloisFieldPolynomial<2>, GaloisFieldPolynomial<2>> result =
        EuclideanDivision<2>(dividend, divisor);
    const GaloisFieldPolynomial<2> quotient = result.first;
    const GaloisFieldPolynomial<2> residual = result.second;

    // X^{1}(X^{1} + 1) + 1
    GaloisFieldPolynomial<2> expect_quotient({1, 1});
    GaloisFieldPolynomial<2> expect_residual({1});
    EXPECT_EQ(expect_quotient, quotient);
    EXPECT_EQ(expect_residual, residual);
  }
}

TEST(polynomial, ToStringTest) {
  // INTEGER
  {
    GaloisFieldPolynomial<2> p({0});
    const std::string actual = p.ToString(EnumPolynomialExpression::INTEGER);
    EXPECT_EQ("0", actual);
  }
  {
    GaloisFieldPolynomial<2> p({1, 1});
    const std::string actual = p.ToString(EnumPolynomialExpression::INTEGER);
    EXPECT_EQ("3", actual);
  }
  {
    GaloisFieldPolynomial<2> p({1, 0, 0, 1});
    const std::string actual = p.ToString(EnumPolynomialExpression::INTEGER);
    EXPECT_EQ("9", actual);
  }
  // COEFFICIENTS
  {
    GaloisFieldPolynomial<2> p(0);
    const std::string actual =
        p.ToString(EnumPolynomialExpression::COEFFICIENTS);
    EXPECT_EQ("0", actual);
  }
  {
    GaloisFieldPolynomial<2> p({1, 1});
    const std::string actual =
        p.ToString(EnumPolynomialExpression::COEFFICIENTS);
    EXPECT_EQ("1  1", actual);
  }
  {
    GaloisFieldPolynomial<2> p({1, 0, 0, 1});
    const std::string actual =
        p.ToString(EnumPolynomialExpression::COEFFICIENTS);
    EXPECT_EQ("1  0  0  1", actual);
  }
  // POLYNOMIAL
  {
    GaloisFieldPolynomial<2> p(0);
    const std::string actual = p.ToString(EnumPolynomialExpression::POLYNOMIAL);
    EXPECT_EQ("0", actual);
  }
  {
    GaloisFieldPolynomial<2> p({1, 1});
    const std::string actual = p.ToString(EnumPolynomialExpression::POLYNOMIAL);
    EXPECT_EQ("1X^{1} + 1", actual);
  }
  {
    GaloisFieldPolynomial<2> p({1, 0, 0, 1});
    const std::string actual = p.ToString(EnumPolynomialExpression::POLYNOMIAL);
    EXPECT_EQ("1X^{3} + 0X^{2} + 0X^{1} + 1", actual);
  }
}
}  // namespace gns
