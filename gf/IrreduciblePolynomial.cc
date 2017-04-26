#include "gf/IrreduciblePolynomial.h"
#include "gf/util.h"

namespace gf {
  template <int N>
  IrreduciblePolynomialGenerator<N>::IrreduciblePolynomialGenerator()
  : seed_(N)
  {
  }

  template <int N>
  std::vector<Polynomial<N>>
  IrreduciblePolynomialGenerator<N>::operator()(const size_t num) const
  {
    std::vector<Polynomial<N>> polynomials(0);
    size_t count = N;

    // find num irredusible polymonials
    for (int numIrreducible = 0; numIrreducible < num; ++numIrreducible) {
      polynomials.push_back(this->findIrreduciblePolynomial(count));
    }

    return polynomials;
  }

  template <int N>
  Polynomial<N>
  IrreduciblePolynomialGenerator<N>::getNext()
  {
    return findIrreduciblePolynomial(seed_);
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

  template <int N>
  Polynomial<N>
  IrreduciblePolynomialGenerator<N>::findIrreduciblePolynomial(
      size_t& seed) const
  {
    const size_t maxLoop = 50;
    // check irreducibility from seed to seed + maxLoop
    for (size_t i = seed; i < seed + maxLoop; ++i) {
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
        seed = i + 1;
        return polynomial;
      }
    }
    // not found
    return Polynomial<2>(0);
  }
} // namespace gf

namespace gf {
  // Base = 2
  template
  IrreduciblePolynomialGenerator<2>::IrreduciblePolynomialGenerator();
  template
  std::vector<Polynomial<2>>
  IrreduciblePolynomialGenerator<2>::operator()(const size_t num) const;
  template
  Polynomial<2>
  IrreduciblePolynomialGenerator<2>::getNext();
  template
  Polynomial<2>
  IrreduciblePolynomialGenerator<2>::findIrreduciblePolynomial(
      size_t& seed) const;
} // namespace gf
