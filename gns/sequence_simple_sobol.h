#pragma once
#include <vector>
#include <cstddef>

namespace gns {
constexpr unsigned int MAX_BIT = 31;
constexpr double NORMALIZE_FACTOR = 0.5 / (double)(1UL << (MAX_BIT - 1UL));

class SimpleSobolGrayMap {
//private typedef
private:
//public typedef
public:
//public function
public:
  SimpleSobolGrayMap(const size_t dimension);
  std::vector<double> Next();
//private function
private:
//private members
private:
  size_t dimension_;
  std::vector<size_t> premitive_polynomials_;
  std::vector<std::vector<size_t>> direction_numbers_;
  std::vector<size_t> number_;
  std::vector<double> points_;
  size_t counter_;
  bool is_first_;
};
} // namespace gns
