#pragma once
#include <random>

namespace gns {
namespace test_util {
  class RandomNumber {
  //private typedef
  private:
  //public typedef
  public:
  //public function
  public:
    RandomNumber(const std::size_t seed = 3252352);
    /**
     * @brief random value in [0, 1). 
     *
     * @return random value in [0, 1).
     */
    double operator()();
    /**
     * @brief [min, max)
     *
     * @param min
     * @param max
     *
     * @return [min, max) 
     */
    double operator()(const double min, const double max);
  //private function
  private:
  //private members
  private:
      std::mt19937 engine_;
      std::uniform_real_distribution<double> distribution_;
  }; // class RandomNumber {
} // namespace test_util
} // namespace gns
