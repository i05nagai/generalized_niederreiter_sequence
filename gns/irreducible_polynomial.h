#pragma once
#include <vector>
#include "gns/polynomial.h"

namespace gns {
/**
 * @brief
 *
 * @tparam Base
 */
template <int Base>
class IrreduciblePolynomialGenerator {
 public:
  /**
   * @brief
   *
   */
  IrreduciblePolynomialGenerator();
  /**
   * @brief Read irreducible polynomials from a file or input stream.
   *  The file contains lines of integers converting from polynomial to integer.
   *  The sequence of integers should be in inceasing order.
   *  The last of the integer is set to seed_.
   *
   * @param inputStream
   */
  explicit IrreduciblePolynomialGenerator(std::istream& inputStream);
  /**
   * @brief 
   *
   * @param 
   */
  explicit IrreduciblePolynomialGenerator(const bool use_prepared_irreducibles);
  /**
   * @brief Find num irreducible polyonmials from degree 1.
   *
   * @param num number of irreducible polynomials generated.
   *
   * @return 
   */
  const std::vector<GaloisFieldPolynomial<Base>>& operator()(const size_t num);
  /**
   * @brief Save irreducible polynomials to output stream.
   * Each irreducible polynomial writes in each line.
   *
   * @param output
   * @param delimiter default value is empty.
   */
  void Save(std::ostream& output, const std::string delimiter="") const;
 private:
  /**
   * @brief
   *
   * @param num
   *
   * @return
   */
  GaloisFieldPolynomial<Base> ConvertToPolynomial(size_t num) const;
  /**
   * @brief This function assumes that seed_ is equal to integer
   * which is converted from irreducibles_.back().
   * seed_ is updated to integer which is converted from
   * the returns value.
   *
   * @return an irreducible polynomial after the seed_.
   * The order is defined by the Base adic expansion mapping.
   */
  GaloisFieldPolynomial<Base> FindIrreduciblePolynomial();
  /**
   * @brief Get prepared irreducible polynomials.
   * Currently up to 20,000 irreducible polynomials are supported.
   *
   * @return 
   */
  std::vector<GaloisFieldPolynomial<Base>>
  GetPreparedIrreducibles(const bool use_prepared_irreducibles) const;
 private:
  /**
   * @brief seed_ must be equal to integer of irreducible_.back().
   */
  size_t seed_;
  /**
   * @brief irreducibles_ must contains all irreducible polynomials of which
   * integer is less than seed_.
   */
  std::vector<GaloisFieldPolynomial<Base>> irreducibles_;
};
/**
 * @brief 
 *
 * @tparam Base
 *
 * @return Pre calcualted irreducible polynomials over Base as a list of int.
 */
template <int Base>
std::vector<int> GetPreparedIrreduciblesData();
/**
 * @brief 
 *
 * @tparam Base
 * @param str_data
 *
 * @return 
 */
template <int Base>
GaloisFieldPolynomial<Base> MakeGaloisFieldPolynomial(const char* str_data);
}  // namespace gns
