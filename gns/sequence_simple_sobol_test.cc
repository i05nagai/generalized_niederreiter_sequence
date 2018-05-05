#include "gns/sequence_simple_sobol.h"
#include <gtest/gtest.h>
#include "gns/irreducible_polynomial.h"
#include "gns/matrix_func.h"
#include "gns/test_util/gtest_assertion.h"

namespace gns {
TEST(SimpleSobolGrayMap, ConstructorTest)
{
   SimpleSobolGrayMap generator(1);
   const std::vector<double> actual = generator.Next();
   const std::vector<double> expect = {0.0};

  GNS_EXPECT_VECTOR_ELEMENT_EQ(expect, actual);
}

TEST(SimpleSobolGrayMap, NextTest)
{
   SimpleSobolGrayMap generator(1);
   const std::vector<std::vector<double>> expects = {
     {
       0.0
     },
     {
       0.5
     },
     {
       0.75
     },
     {
       0.25
     },
     {
       0.375
     },
     {
       0.875
     },
     {
       0.625
     },
     {
       0.125
     },
   };

   for (size_t i = 0; i < expects.size(); ++i) {
     const std::vector<double> actual = generator.Next();
    GNS_EXPECT_VECTOR_ELEMENT_EQ(expects[i], actual);
   }
}

TEST(SimpleSobolGrayMap, NextTest2)
{
   SimpleSobolGrayMap generator(2);
   const std::vector<std::vector<double>> expects = {
     {
       0.0, 0.0
     },
     {
       0.5, 0.5
     },
     {
       0.75, 0.25
     },
     {
       0.25, 0.75
     },
     {
       0.375, 0.125,
     },
     {
       0.875, 0.625,
     },
     {
       0.625, 0.375
     },
     {
       0.125, 0.875,
     },
   };

   for (size_t i = 0; i < expects.size(); ++i) {
     const std::vector<double> actual = generator.Next();
    GNS_EXPECT_VECTOR_ELEMENT_EQ(expects[i], actual);
   }
}
} // namespace gns
