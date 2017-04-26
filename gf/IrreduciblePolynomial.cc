#include "gf/IrreduciblePolynomial.h"
#include "gf/util.h"

namespace gf {
  template <int N>
  IrreduciblePolynomialGenerator<N>::IrreduciblePolynomialGenerator(
      const size_t base, const size_t baseDigits)
  : base_(base),
    baseDigits_(baseDigits)
  {
  }

  template <int N>
  std::vector<Polynomial<N>>
  IrreduciblePolynomialGenerator<N>::operator()(const size_t num) const
  {
    std::vector<Polynomial<N>> polynomials(0);
    size_t count = N;
    const size_t maxLoop = 50;

    // find num irredusible polymonials
    for (int numIrreducible = 0; numIrreducible < num; ++numIrreducible) {

      // check irreducibility from count to count + maxLoop
      for (size_t i = count; i < count + maxLoop; ++i) {
        bool isReducible = false;
        Polynomial<N> polynomial = this->convertToPolynomial(i);

        // check dividable or not
        for (size_t divisorCount = N; divisorCount < i; ++divisorCount) {
          Polynomial<N> divisor = this->convertToPolynomial(divisorCount);
          std::pair<Polynomial<N>, Polynomial<N>> result 
            = euclidean_division(polynomial, divisor);
          const Polynomial<N>& residual = result.second;
          // dividable
          if (residual.isZero()) {
            isReducible = true;
            break;
          }
        }
        // irreducible
        if (!isReducible) {
          polynomials.emplace_back(polynomial);
          count = i + 1;
          break;
        }
      }
    }

    return polynomials;
  }

  template <int N>
  size_t IrreduciblePolynomialGenerator<N>::calcDegree(size_t num) const
  {
    size_t degree = 0;
    while (num > 0) {
      num >>= baseDigits_;
      degree++;
    }
    return degree;
  }

  template <int N>
  Polynomial<N>
  IrreduciblePolynomialGenerator<N>::convertToPolynomial(const size_t num) const
  {
    std::pair<size_t, std::unique_ptr<unsigned char[]>> result 
      = calcBaseAdic<N>(num);
    const size_t arraySize = result.first;
    return Polynomial<N>(arraySize, std::move(result.second));
  }
} // namespace gf

namespace gf {
  template
  IrreduciblePolynomialGenerator<2>::IrreduciblePolynomialGenerator(
      const size_t base, const size_t baseDigits);
  template
  std::vector<Polynomial<2>>
  IrreduciblePolynomialGenerator<2>::operator()(const size_t num) const;
  template
  size_t IrreduciblePolynomialGenerator<2>::calcDegree(size_t num) const;
} // namespace gf
