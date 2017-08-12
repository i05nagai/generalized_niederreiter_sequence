#pragma once
#include "gns/polynomial.h"
#include <vector>

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
   * @brief Read irreducible polynomials from a file or input stream.
   *  The file contains lines of integers converting from polynomial to integer.
   *  The sequence of integers should be in inceasing order.
   *  The last of the integer is set to seed_.
   *
   * @param inputStream
   */
  IrreduciblePolynomialGenerator(std::istream& inputStream);
  /**
   * @brief Find num irreducible polyonmials from degree 1.
   *
   * @param num number of irreducible polynomials generating.
   *
   * @return 
   */
  const std::vector<GaloisFieldPolynomial<Base>>& operator()(const size_t num);
  /**
   * @brief 
   *
   * @return 
   */
  GaloisFieldPolynomial<Base> GetNext();
  /**
   * @brief Save irreducible polynomials to filepath.
   *
   * @param filepath
   */
  void Save(std::ostream& output) const;
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
   * @brief 
   *
   * @return 
   */
  GaloisFieldPolynomial<Base> FindIrreduciblePolynomial(size_t& seed) const;
private:
  size_t seed_;
  std::vector<GaloisFieldPolynomial<Base>> irreducibles_;
};

template <int Base>
GaloisFieldPolynomial<Base>
MakeGaloisFieldPolynomial(const char* str_data);
} // namespace gns
