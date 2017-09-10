#include "gns/galois_field.h"
#include <gtest/gtest.h>
#include "gns/test_util/gtest_assertion.h"
#include "gns/test_util/test_data.h"

namespace gns {
template <int Base>
void CheckOperatorAssignAdd() {
  std::vector<GaloisField<Base>> data 
    = test_util::TestData::GetRandomGaloisFieldVector<Base>(2);
  GaloisField<Base> e1 = data[0];
  GaloisField<Base> e2 = data[1];
  e1 += e2;
  GaloisField<Base> expect = data[0] + data[1];
  EXPECT_EQ(expect, e1);
}

TEST(galois_field_test, GaloisFieldOperatorAssignAdd)
{
  CheckOperatorAssignAdd<2>();
  CheckOperatorAssignAdd<4>();
  CheckOperatorAssignAdd<16>();
}

template <int Base>
void CheckOperatorAssignMinus() {
  std::vector<GaloisField<Base>> data
    = test_util::TestData::GetRandomGaloisFieldVector<Base>(2);
  GaloisField<Base> e1 = data[0];
  GaloisField<Base> e2 = data[1];
  e1 -= e2;
  GaloisField<Base> expect = data[0] - data[1];
  EXPECT_EQ(expect, e1);
}

TEST(galois_field_test, GaloisFieldOperatorAssignMinus)
{
  CheckOperatorAssignMinus<2>();
  CheckOperatorAssignMinus<4>();
  CheckOperatorAssignMinus<16>();
}

template <int Base>
void CheckOperatorAssignMultiply() {
  std::vector<GaloisField<Base>> data
    = test_util::TestData::GetRandomGaloisFieldVector<Base>(2);
  GaloisField<Base> e1 = data[0];
  GaloisField<Base> e2 = data[1];
  e1 *= e2;
  GaloisField<Base> expect = data[0] * data[1];
  EXPECT_EQ(expect, e1);
}

TEST(galois_field_test, GaloisFieldOperatorAssignMultiply)
{
  CheckOperatorAssignMultiply<2>();
  CheckOperatorAssignMultiply<4>();
  CheckOperatorAssignMultiply<16>();
}

template <int Base>
void CheckOperatorAssignDivision() {
  std::vector<GaloisField<Base>> data
    = test_util::TestData::GetRandomGaloisFieldVector<Base>(2);
  GaloisField<Base> e1 = data[0];
  GaloisField<Base> e2 = data[1];
  e1 /= e2;
  GaloisField<Base> expect = data[0] / data[1];
  EXPECT_EQ(expect, e1);
}

TEST(galois_field_test, GaloisFieldOperatorAssignDivision)
{
  CheckOperatorAssignDivision<2>();
  CheckOperatorAssignDivision<4>();
  CheckOperatorAssignDivision<16>();
}
}
