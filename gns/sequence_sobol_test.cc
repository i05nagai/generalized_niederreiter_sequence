#include "gns/sequence_sobol.h"
#include <gtest/gtest.h>
#include "gns/irreducible_polynomial.h"
#include "gns/matrix_func.h"
#include "gns/test_util/gtest_assertion.h"

namespace gns {
TEST(sequence_sobol_test, MakeSobolGeneratorMatrix1) {
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

TEST(sequence_sobol_test, MakeSobolGeneratorMatrix4) {
  const size_t max_bit = 24;
  const size_t dim = 7;
  IrreduciblePolynomialGenerator<2> irreducible_generator;
  std::vector<GaloisFieldPolynomial<2>> irreducibles =
      irreducible_generator(dim);
  Matrix<2> matrix = MakeSobolGeneratorMatrix(dim, irreducibles, max_bit);
  std::vector<GaloisField<2>> expect = {
      // clang-format off
    0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1,
    0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0,
    0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1,
    1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,
    0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0,
    0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
      // clang-format on
  };
  for (size_t row = 0; row < matrix.RowSize(); ++row) {
    for (size_t col = 0; col < matrix.ColSize(); ++col) {
      const size_t pos = row * matrix.ColSize() + col;
      EXPECT_EQ(expect[pos], matrix(row, col));
    }
  }
}

TEST(sequence_sobol_test, MakeSobolGeneratorMatrix2) {
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

TEST(sequence_sobol_test, NextBase2) {
  // dim=1
  {
    std::vector<double> expect({
                              // clang-format off
                               0.0, 0.5,
                               0.25, 0.75,
                               0.125, 0.625, 0.375, 0.875,
                               0.0625, 0.5625, 0.3125, 0.8125, 0.1875, 0.6875,
                               0.4375, 0.9375,
                              // clang-format on
                               });
    Sobol<2> sobol(1);
    for (size_t i = 0; i < expect.size(); ++i) {
      std::unique_ptr<double[]> point = sobol.Next();
      EXPECT_DOUBLE_EQ(expect[i], point[0]);
    }
  }
  // dim =2
  {
    std::vector<std::vector<double>> expect({
    // clang-format off
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
    // clang-format on
    });
    Sobol<2> sobol(2);
    for (size_t i = 0; i < expect.size(); ++i) {
      std::unique_ptr<double[]> point = sobol.Next();
      EXPECT_DOUBLE_EQ(expect[i][0], point[0]);
      EXPECT_DOUBLE_EQ(expect[i][1], point[1]);
    }
  }
}

TEST(sequence_sobol_test, SobolGrayMapNextBase2Dim1) {
  std::vector<double> expect({
                            // clang-format off
                             0.0, 0.5,
                             0.75, 0.25,
                             0.375, 0.875, 0.625, 0.125,
                             0.1875, 0.6875, 0.9375, 0.4375, 0.3125, 0.8125,
                             0.5625, 0.0625,
                            // clang-format on
                            });
  SobolGrayMap<2> sobol(1);
  for (size_t i = 0; i < expect.size(); ++i) {
    const std::unique_ptr<double[]>& point = sobol.Next();
    EXPECT_DOUBLE_EQ(expect[i], point[0]);
  }
}

TEST(sequence_sobol_test, SobolGrayMapNextBase2Dim2) {
  std::vector<std::vector<double>> expect({
  // clang-format off
    { 0.0, 0.0 },
    { 0.5, 0.5 },
    { 0.75, 0.25 },
    { 0.25, 0.75 },
    { 0.375, 0.375 },
    { 0.875, 0.875 },
    { 0.625, 0.125 },
    { 0.125, 0.625 },
    { 0.1875, 0.3125 },
    { 0.6875, 0.8125 },
    { 0.9375, 0.0625 },
    { 0.4375, 0.5625 },
    { 0.3125, 0.1875 },
    { 0.8125, 0.6875 },
    { 0.5625, 0.4375 },
    { 0.0625, 0.9375 },
  // clang-format on
  });
  SobolGrayMap<2> sobol(2);
  for (size_t i = 0; i < expect.size(); ++i) {
    const std::unique_ptr<double[]>& point = sobol.Next();
    EXPECT_DOUBLE_EQ(expect[i][0], point[0]);
    EXPECT_DOUBLE_EQ(expect[i][1], point[1]);
  }
}

/*--------------------------------------------------------------------------
 * Base 4
 *------------------------------------------------------------------------*/
TEST(sequence_sobol_test, NextBase4Dim1) {
  std::vector<double> expect({
                             // clang-format off
                             0.0    , 0.25   , 0.5    , 0.75   , 0.0625 ,
                             0.3125 , 0.5625 , 0.8125 , 0.125  , 0.375  ,
                             0.625  , 0.875  , 0.1875 , 0.4375 , 0.6875 ,
                             0.9375 ,
                             // clang-format on
                             });
  Sobol<4> sobol(1);
  for (size_t i = 0; i < expect.size(); ++i) {
    std::unique_ptr<double[]> point = sobol.Next();
    EXPECT_DOUBLE_EQ(expect[i], point[0]);
  }
}

TEST(sequence_sobol_test, NextBase4Dim2) {
  std::vector<std::vector<double>> expect({
  // clang-format off
    { 0.0, 0.0 },
    { 0.25, 0.25 },
    { 0.5, 0.5 },
    { 0.75, 0.75 },
    { 0.0625, 0.3125 },
    { 0.3125, 0.0625 },
    { 0.5625, 0.8125 },
    { 0.8125, 0.5625 },
    { 0.125, 0.625 },
    { 0.375, 0.875 },
    { 0.625, 0.125 },
    { 0.875, 0.375 },
    { 0.1875, 0.9375 },
    { 0.4375, 0.6875 },
    { 0.6875, 0.4375 },
    { 0.9375, 0.1875 },
  // clang-format on
  });
  Sobol<4> sobol(2);
  for (size_t i = 0; i < expect.size(); ++i) {
    std::unique_ptr<double[]> point = sobol.Next();
    EXPECT_DOUBLE_EQ(expect[i][0], point[0]);
    EXPECT_DOUBLE_EQ(expect[i][1], point[1]);
  }
}

TEST(sequence_sobol_test, SobolGrayMapFindCoefficientBase4) {
  SobolGrayMap<4> sobol(1);
  std::vector<size_t> data = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16,
  };
  std::vector<size_t> expect_ls = {
      // clang-format off
    0, // 1  = 1
    0, // 2  = 2
    0, // 3  = 3
    1, // 4  = 10
    0, // 5  = 11
    0, // 6  = 12
    0, // 7  = 13
    1, // 8  = 20
    0, // 9  = 21
    0, // 10 = 22
    0, // 11 = 23
    1, // 12 = 30
    0, // 13 = 31
    0, // 14 = 32
    0, // 15 = 33
    2, // 16 = 100
      // clang-format on
  };
  std::vector<size_t> expect_coeffs = {
      // clang-format off
    1, // 1, 1, l(n)=0, 1-0=1=0b01 (mod Base),
    3, // 2, 2, l(n)=0, 2-0=2=0b10,
    1, // 3, 3, l(n)=0, 3-0=3=0b11,
    1, // 4, 10 l(n)=1, 1-0=1=0b01,
    3, // 5, 11,l(n)=0, 1-1=0=0b00,
    1, // 6, 12,l(n)=0, 2-1=1=0b01,
    3, // 7, 13,l(n)=0, 3-1=2=0b10,
    3, // 8, 20,l(n)=1, 2-0=2=0b10,
    1, // 9, 21,l(n)=0, 1-2=3=0b11,
    3, // 10, 22,l(n)=1,2-0=2=0b10,
    1, // 11, 23,l(n)=0,3-2=1
    1, // 12, 30,l(n)=1,3-0=3
    3, // 13, 31,l(n)=0,1-3=2
    1, // 14, 32,l(n)=0,2-3=3
    3, // 15, 33,l(n)=0,3-3=0
    1, // 16, 100,l(n)=2,1-0=1
      // clang-format on
  };

  for (size_t i = 0; i < data.size(); ++i) {
    const size_t num = data[i];
    size_t l = 0;
    const GaloisField<4> actual = sobol.FindCoefficient(num, l);
    // expect
    const size_t expect_l = expect_ls[i];
    const size_t expect_coeff = expect_coeffs[i];
    GNS_EXPECT_EQ_WITH_INDEX(expect_l, l, i)
    GNS_EXPECT_EQ_WITH_INDEX(expect_coeff, actual.value(), i)
  }
}


TEST(sequence_sobol_test, SobolGrayMapNextBase4Dim1) {
  // dim=1
  std::vector<double> expect({
                             0.0    ,
                             0.25   ,
                             0.5    ,
                             0.75   ,
                             0.8125 ,
                             0.0625 ,
                             0.3125 ,
                             0.5625 ,
                             0.625  ,
                             0.875  ,
                             0.125  ,
                             0.375  ,
                             0.4375 ,
                             0.6875 ,
                             0.9375 ,
                             0.1875 ,
                             });
  SobolGrayMap<4> sobol(1);
  for (size_t i = 0; i < expect.size(); ++i) {
    const std::unique_ptr<double[]>& point = sobol.Next();
    GNS_EXPECT_DOUBLE_EQ_WITH_INDEX(expect[i], point[0], i);
  }

}

TEST(sequence_sobol_test, SobolGrayMapNextBase4Dim2) {
  // dim =2
  {
    std::vector<std::vector<double>> expect({
    // clang-format off
      { 0.0, 0.0 },
      { 0.25, 0.25 },
      { 0.5, 0.5 },
      { 0.75, 0.75 },
      { 0.8125, 0.5625 },
      { 0.0625, 0.3125 },
      { 0.3125, 0.0625 },
      { 0.5625, 0.8125 },
      { 0.625, 0.125 },
      { 0.875, 0.375 },
      { 0.125, 0.625 },
      { 0.375, 0.875 },
      { 0.4375, 0.6875 },
      { 0.6875, 0.4375 },
      { 0.9375, 0.1875 },
      { 0.1875, 0.9375 },
    // clang-format on
    });
    SobolGrayMap<4> sobol(2);
    for (size_t i = 0; i < expect.size(); ++i) {
      const std::unique_ptr<double[]>& point = sobol.Next();
      GNS_EXPECT_DOUBLE_EQ_WITH_INDEX(expect[i][0], point[0], i);
      GNS_EXPECT_DOUBLE_EQ_WITH_INDEX(expect[i][1], point[1], i);
    }
  }
}
}  // namespace gns
