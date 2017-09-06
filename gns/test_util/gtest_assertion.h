#pragma once
#include <gtest/gtest.h>
#include "gns/fwd.h"

#define GNS_EXPECT_VECTOR_ELEMENT_EQ(expect, actual) \
  EXPECT_TRUE(gns::IsElementEqual(expect, actual));

#define GNS_EXPECT_GALOIS_FIELD_OP(test_case, op) \
  EXPECT_TRUE(gns::IsGaloisFieldOperatorCorrect(test_case, op));

#define GNS_EXPECT_EQ_WITH_INDEX(expect, actual, index) \
  EXPECT_TRUE(gns::IsExpectEqualWithIndex(expect, actual, index));

#define GNS_EXPECT_DOUBLE_EQ_WITH_INDEX(expect, actual, index) \
  EXPECT_TRUE(gns::IsExpectEqualWithIndex(expect, actual, index));

namespace gns {
template <typename T1, typename T2>
inline ::testing::AssertionResult IsElementEqual(const std::vector<T1>& v1,
                                                 const std::vector<T2>& v2) {
  if (v1.size() != v2.size()) {
    return ::testing::AssertionFailure() << "size of vector is not same";
  }
  for (size_t i = 0; i < v1.size(); ++i) {
    if (v1[i] != v2[i]) {
      return ::testing::AssertionFailure()
             << i - 1 << " th element is different. "
             << " expect: " << static_cast<int>(v1[i]) << ", "
             << " actual: " << static_cast<int>(v2[i]);
    }
  }
  return ::testing::AssertionSuccess();
}

template <int Base>
inline ::testing::AssertionResult IsGaloisFieldOperatorCorrect(
    const std::vector<GaloisField<Base>>& test_case,
    std::function<GaloisField<Base>(const GaloisField<Base>&,
                                    const GaloisField<Base>&)>
        operation) {
  // left, right, expect
  // where left op right = expect
  if (test_case.size() % 3 != 0) {
    return ::testing::AssertionFailure() << "invalid test case.";
  }
  for (size_t i = 0; i < test_case.size(); i += 3) {
    const auto expect = operation(test_case[i], test_case[i + 1]);
    if (expect != test_case[i + 2]) {
      return ::testing::AssertionFailure()
             << (i / 3) << " th test_case is different. " << test_case[i]
             << " op " << test_case[i + 1] << ", "
             << " expect: " << expect.value() << ", "
             << " actual: " << test_case[i + 2];
    }
  }
  return ::testing::AssertionSuccess();
}

template <typename T1, typename T2, typename Index>
inline ::testing::AssertionResult IsExpectEqualWithIndex(const T1& expect,
                                                         const T2& actual,
                                                         const Index& i) {
  if (expect != actual) {
    return ::testing::AssertionFailure() << i << " th test is different. "
                                         << " expect: " << expect << ", "
                                         << " actual: " << actual;
  }
  return ::testing::AssertionSuccess();
}
}  // namespace gns
