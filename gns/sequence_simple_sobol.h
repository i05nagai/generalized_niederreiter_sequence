#pragma once
#include <vector>
#include <cstddef>

namespace gns {
constexpr unsigned int MAX_BIT = 31;
constexpr double NORMALIZE_FACTOR = 0.5 / (double)(1UL << (MAX_BIT - 1UL));

/**
 * @brief Fast and simple sobol sequence.
 */
class SimpleSobolGrayMap {
//private typedef
private:
//public typedef
public:
//public function
public:
  /**
   * @brief 
   *
   * @param dimension
   */
  SimpleSobolGrayMap(const size_t dimension);
  /**
   * @brief get next points.
   *
   * @return 'dimension'-dim sobol sequence.
   */
  std::vector<double> Next();
//private function
private:
//private members
private:
  /**
   * @brief 
   */
  size_t dimension_;
  /**
   * @brief 
   */
  std::vector<size_t> premitive_polynomials_;
  /**
   * @brief 
   */
  std::vector<std::vector<size_t>> direction_numbers_;
  /**
   * @brief 
   */
  std::vector<size_t> number_;
  /**
   * @brief 
   */
  std::vector<double> points_;
  size_t counter_;
  /**
   * @brief 
   */
  bool is_first_;
};
} // namespace gns
