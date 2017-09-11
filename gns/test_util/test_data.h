#pragma once
#include <memory>
#include "gns/polynomial.h"

namespace gns {
namespace test_util {
class TestData {
  // private typedef
 private:
  // public typedef
 public:
  // public function
 public:
  /**
   * @brief
   *
   * @param size
   *
   * @return vector of which element are in [0, 1).
   */
  static std::vector<double> GetRandomNumbers(const size_t size);
  /**
   * @brief
   *
   * @param size
   * @param base
   *
   * @return
   */
  template <int Base>
  static std::vector<GaloisField<Base>> GetRandomGaloisFieldVector(
      const size_t size);
  /**
   * @brief
   *
   * @param size
   * @param base
   *
   * @return
   */
  template <int Base>
  static std::unique_ptr<GaloisField<Base>[]> GetRandomGaloisFieldArray(
      const size_t size);
  /**
   * @brief
   *
   * @param degree
   * @param base
   *
   * @return
   */
  template <int Base>
  static std::unique_ptr<GaloisField<Base>[]> GetPolynomialCoefficients(
      const size_t degree);
  /**
   * @brief
   *
   * @param degree
   * @param base
   *
   * @return
   */
  template <int Base>
  static gns::GaloisFieldPolynomial<Base> GetRandomPolynomial(
      const size_t degree);
  // private function
 private:
  /**
   * @brief
   *
   * @param data should be from 0 to 1
   * @param base
   *
   * @return
   */
  template <int Base>
  static GaloisField<Base> DoubleToGaloisField(const double data);
  // private members
 private:
};  // class TestData {

/**
 * @brief
 *
 * @tparam Base
 * @param max_degree
 * @param data
 *
 * @return
 */
template <int Base>
std::unique_ptr<GaloisField<Base>[]> MakeGaloisFieldArray(
    std::initializer_list<unsigned int> data);
}  // namespace test_util
}  // namespace gns
