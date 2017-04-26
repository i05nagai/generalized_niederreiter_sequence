#pragma once
#include "gf/Polynomial.h"
#include <vector>

namespace gf {
  template <int N>
  class IrreduciblePolynomialGenerator {
  public:
    IrreduciblePolynomialGenerator(const size_t base, const size_t baseDigits);
    std::vector<Polynomial<N>> operator()(const size_t num) const;
  private:
    size_t calcDegree(size_t num) const;
    Polynomial<N> convertToPolynomial(size_t num) const;
  private:
    size_t base_;
    size_t baseDigits_;
  };
} // namespace gf
