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
     * @param base
     * @param baseDigits
     */
    IrreduciblePolynomialGenerator();
    /**
     * @brief 
     *
     * @param num
     *
     * @return 
     */
    std::vector<Polynomial<N>> operator()(const size_t num) const;
    /**
     * @brief 
     *
     * @return 
     */
    Polynomial<N> getNext();
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
  };
} // namespace gf
