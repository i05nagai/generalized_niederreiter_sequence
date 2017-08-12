#include "gns/test_util/random_number.h"

namespace gns {
namespace test_util {
RandomNumber::RandomNumber(const size_t seed) : engine_(), distribution_() {
  engine_.seed(seed);
}

double RandomNumber::operator()() { return distribution_(engine_); }

double RandomNumber::operator()(const double min, const double max) {
  const int diff = max - min;
  return (*this)() * diff + min;
}
}  // namespace test_util
}  // namespace gns
