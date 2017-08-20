#include "gns/sequence_sobol.h"
#include <gtest/gtest.h>
#include "gns/irreducible_polynomial.h"
#include "gns/matrix_func.h"

namespace gns {
TEST(sequence_sobol, MakeSobolGeneratorMatrixTest1) {
  // dim = 1
  const size_t dim = 1;
  const size_t max_bit = 32;
  IrreduciblePolynomialGenerator<2> irreducible_generator;
  std::vector<GaloisFieldPolynomial<2>> irreducibles =
      irreducible_generator(dim);
  Matrix<2> matrix = MakeSobolGeneratorMatrix(dim, irreducibles, max_bit);

  // indentity matrix
  EXPECT_TRUE(IsIdentity(matrix));
}

TEST(sequence_sobol, MakeSobolGeneratorMatrixTest2) {
  // dim = 2
  const size_t max_bit = 24;
  const size_t dim = 2;
  IrreduciblePolynomialGenerator<2> irreducible_generator;
  std::vector<GaloisFieldPolynomial<2>> irreducibles =
      irreducible_generator(dim);
  Matrix<2> matrix = MakeSobolGeneratorMatrix(dim, irreducibles, max_bit);
  std::vector<GaloisField<2>> expect = {
      // clang-format off
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
  0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      // clang-format on
  };
  for (size_t row = 0; row < matrix.RowSize(); ++row) {
    for (size_t col = 0; col < matrix.ColSize(); ++col) {
      const size_t pos = row * matrix.ColSize() + col;
      EXPECT_EQ(expect[pos], matrix(row, col));
    }
  }
}

TEST(sequence_sobol, NextTest) {
  // dim=1
  {
    std::vector<double> expect({0.0, 0.5, 0.25, 0.75});
    Sobol<2> sobol(1);
    for (size_t i = 0; i < expect.size(); ++i) {
      std::unique_ptr<double[]> point = sobol.Next();
      EXPECT_DOUBLE_EQ(expect[i], point[0]);
    }
  }
  // dim =2
  {
    std::vector<std::vector<double>> expect({
        {0.0, 0.0},
        {0.5, 0.5},
        {0.25, 0.75},
        {0.75, 0.25},
        {0.125, 0.625},
        {0.625, 0.125},
        {0.375, 0.375},
        {0.875, 0.875},
        {0.0625, 0.9375},
        {0.5625, 0.4375},
    });
    Sobol<2> sobol(2);
    for (size_t i = 0; i < expect.size(); ++i) {
      std::unique_ptr<double[]> point = sobol.Next();
      EXPECT_DOUBLE_EQ(expect[i][0], point[0]);
      EXPECT_DOUBLE_EQ(expect[i][1], point[1]);
    }
  }
}
}  // namespace gns
