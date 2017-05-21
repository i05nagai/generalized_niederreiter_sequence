#pragma once
#include "gf/Polynomial.h"
#include <vector>

namespace gf {
  /**
   * @brief 
   *
   * @tparam N
   */
  template <int N>
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
    IrreduciblePolynomialGenerator(std::istream& inputStream);
    /**
     * @brief Find num irreducible polyonmials from degree 1.
     *
     * @param num number of irreducible polynomials generating.
     *
     * @return 
     */
    const std::vector<Polynomial<N>>& operator()(const size_t num);
    /**
     * @brief 
     *
     * @return 
     */
    Polynomial<N> getNext();
    /**
     * @brief Save irreducible polynomials to filepath.
     *
     * @param filepath
     */
    void save(std::ostream& output) const;
  private:
    /**
     * @brief 
     *
     * @param num
     *
     * @return 
     */
    Polynomial<N> convertToPolynomial(size_t num) const;
    /**
     * @brief 
     *
     * @return 
     */
    Polynomial<N> findIrreduciblePolynomial(size_t& seed) const;
  private:
    size_t seed_;
    std::vector<Polynomial<N>> irreducibles_;
  };
} // namespace gf
