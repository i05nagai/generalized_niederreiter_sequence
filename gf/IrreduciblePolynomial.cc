#include "gf/IrreduciblePolynomial.h"
#include "gf/util.h"
#include <iostream>
#include <ios>
#include <sstream>
#include <string>

namespace gf {
  template <int N>
  IrreduciblePolynomialGenerator<N>::IrreduciblePolynomialGenerator()
  : seed_(N), irreducibles_(0)
  {
  }

  template <int N>
  IrreduciblePolynomialGenerator<N>::IrreduciblePolynomialGenerator(
      std::istream& inputStream)
  : seed_(N), irreducibles_(0)
  {
    if (inputStream.fail()) {
       throw std::runtime_error("Read file error!");
    }
    std::unique_ptr<char[]> line(new char[256]);
    // read from input stream
    while (inputStream.getline(line.get(), 256)) {
      irreducibles_.emplace_back(toPolynomial<N>(line.get()));
    }
    // set last polynomial as seed
    seed_ = std::stoul(
        irreducibles_.back().toString(EnumPolynomialExpression::INTEGER));
  }

  template <int N>
  const std::vector<Polynomial<N>>&
  IrreduciblePolynomialGenerator<N>::operator()(const size_t num)
  {
    const size_t numIter = num - irreducibles_.size();

    // if num irreducible polynomials has already founded
    if (numIter <= 0) {
      return irreducibles_;
    }

    // find num irredusible polymonials
    size_t count = seed_;
    for (size_t i = 0; i < numIter; ++i) {
      irreducibles_.push_back(this->findIrreduciblePolynomial(count));
    }

    return irreducibles_;
  }

  template <int N>
  Polynomial<N>
  IrreduciblePolynomialGenerator<N>::getNext()
  {
    irreducibles_.emplace_back(findIrreduciblePolynomial(seed_));
    return irreducibles_.back();
  }

  template <int N>
  void
  IrreduciblePolynomialGenerator<N>::save(std::ostream& output) const
  {
    for (size_t i = 0; i < irreducibles_.size(); ++i) {
      output 
        << irreducibles_[i].toString(EnumPolynomialExpression::INTEGER)
        << std::endl;;
    }
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
    const size_t maxLoop = 5000;
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
  IrreduciblePolynomialGenerator<2>::IrreduciblePolynomialGenerator(
      std::istream& inputStream);
  template
  const std::vector<Polynomial<2>>&
  IrreduciblePolynomialGenerator<2>::operator()(const size_t num);
  template
  Polynomial<2>
  IrreduciblePolynomialGenerator<2>::getNext();
  template
  void
  IrreduciblePolynomialGenerator<2>::save(std::ostream& output) const;
  template
  Polynomial<2>
  IrreduciblePolynomialGenerator<2>::findIrreduciblePolynomial(
      size_t& seed) const;
} // namespace gf
