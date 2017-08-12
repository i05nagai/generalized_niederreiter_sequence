#include "gns/irreducible_polynomial.h"
#include "gns/test_util/gtest_helper_macro.h"
#include <gtest/gtest.h>
#include <sstream>

namespace gns {
TEST(IrreduciblePolynomial, GetNextTest01)
{
  IrreduciblePolynomialGenerator<2> generator;
  GaloisFieldPolynomial<2> actual = generator.GetNext();

  GaloisFieldPolynomial<2> expect({0, 1});
  GSN_EXPECT_POLYNOMIAL_EQ(expect, actual);
}

TEST(IrreduciblePolynomial, GetNextTest02)
{
  std::vector<GaloisFieldPolynomial<2>> expects = {
    {0, 1},
    {1, 1},
    {1, 1, 1},
    {1, 1, 0, 1},
    {1, 0, 1, 1},
    {1, 1, 0, 0, 1},
    {1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1},
  };
  const size_t num = expects.size();
  IrreduciblePolynomialGenerator<2> generator;
  for (size_t i = 0; i < num; ++i) {
    const GaloisFieldPolynomial<2>& actual = generator.GetNext();
    EXPECT_EQ(expects[i], actual);
  }
}

TEST(IrreduciblePolynomial, ConstructorTest)
{
  std::string expect("2\n4\n");
  std::istringstream input_stream(expect);
  IrreduciblePolynomialGenerator<2> generator(input_stream);

  std::stringstream string_stream;
  generator.Save(string_stream);

  EXPECT_EQ(expect, string_stream.str());
}

TEST(IrreduciblePolynomial, OperatorParenthesisTest)
{
  std::vector<GaloisFieldPolynomial<2>> expects = {
    {0, 1},
    {1, 1},
    {1, 1, 1},
    {1, 1, 0, 1},
    {1, 0, 1, 1},
    {1, 1, 0, 0, 1},
    {1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1},
  };
  const size_t num = expects.size();
  IrreduciblePolynomialGenerator<2> generator;
  std::vector<GaloisFieldPolynomial<2>> actual = generator(num);
  for (size_t i = 0; i < num; ++i) {
    EXPECT_EQ(expects[i], actual[i]);
  }
}
} // namespace gf

