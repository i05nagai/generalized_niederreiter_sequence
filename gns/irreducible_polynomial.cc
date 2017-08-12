#include "gns/irreducible_polynomial.h"
//#include "gns/util.h"
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

namespace gns {
template <int Base>
IrreduciblePolynomialGenerator<Base>::IrreduciblePolynomialGenerator(
    std::istream& inputStream)
: seed_(Base), irreducibles_(0)
{
  if (inputStream.fail()) {
     throw std::runtime_error("Read file error!");
  }
  std::unique_ptr<char[]> line(new char[256]);
  // read from input stream
  while (inputStream.getline(line.get(), 256)) {
    irreducibles_.emplace_back(MakeGaloisFieldPolynomial<Base>(line.get()));
  }
  // set last polynomial as seed
  seed_ = std::stoul(
      irreducibles_.back().ToString(EnumPolynomialExpression::INTEGER));
}

template <int Base>
const std::vector<GaloisFieldPolynomial<Base>>&
IrreduciblePolynomialGenerator<Base>::operator()(const size_t num)
{
  const size_t numIter = num - irreducibles_.size();

  // if num irreducible polynomials has already founded
  if (numIter <= 0) {
    return irreducibles_;
  }

  // find num irredusible polymonials
  size_t count = seed_;
  for (size_t i = 0; i < numIter; ++i) {
    irreducibles_.push_back(this->FindIrreduciblePolynomial(count));
  }

  return irreducibles_;
}

template <int Base>
GaloisFieldPolynomial<Base>
IrreduciblePolynomialGenerator<Base>::GetNext()
{
  irreducibles_.emplace_back(FindIrreduciblePolynomial(seed_));
  return irreducibles_.back();
}

template <int Base>
void
IrreduciblePolynomialGenerator<Base>::Save(std::ostream& output) const
{
  for (size_t i = 0; i < irreducibles_.size(); ++i) {
    output 
      << irreducibles_[i].ToString(EnumPolynomialExpression::INTEGER)
      << std::endl;
  }
}

template <int Base>
GaloisFieldPolynomial<Base>
IrreduciblePolynomialGenerator<Base>::ConvertToPolynomial(
    const size_t num) const
{
  std::pair<size_t, std::unique_ptr<GaloisField<Base>[]>> result 
    = CalculateBaseAdic<Base>(num);
  const size_t arraySize = result.first;
  return GaloisFieldPolynomial<Base>(arraySize, std::move(result.second));
}

template <int Base>
GaloisFieldPolynomial<Base>
IrreduciblePolynomialGenerator<Base>::FindIrreduciblePolynomial(
    size_t& seed) const
{
  const size_t maxLoop = 5000;
  // check irreducibility from seed to seed + maxLoop
  for (size_t i = seed; i < seed + maxLoop; ++i) {
    bool isReducible = false;
    GaloisFieldPolynomial<Base> polynomial = this->ConvertToPolynomial(i);

    // check dividable or not
    for (size_t divisorCount = Base; divisorCount < i; ++divisorCount) {
      GaloisFieldPolynomial<Base> divisor = this->ConvertToPolynomial(divisorCount);
      std::pair<
        GaloisFieldPolynomial<Base>, GaloisFieldPolynomial<Base>
        > result = EuclideanDivision(polynomial, divisor);
      const GaloisFieldPolynomial<Base>& residual = result.second;
      // dividable
      if (residual.IsZero()) {
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
  return GaloisFieldPolynomial<2>(0);
}

/*--------------------------------------------------------------------------
 * free functions
 *------------------------------------------------------------------------*/
template <int Base>
GaloisFieldPolynomial<Base>
MakeGaloisFieldPolynomial(const char* str_data)
{
  size_t data = atoi(str_data);
  std::pair<size_t, std::unique_ptr<GaloisField<Base>[]>> degree_and_coeffs 
    = CalculateBaseAdic<Base>(data);
  const size_t& degree = degree_and_coeffs.first;
  return GaloisFieldPolynomial<Base>(
      degree, std::move(degree_and_coeffs.second));
}

} // namespace gns

namespace gns {
#define TEMPLATE_INSTANTIATION(Base)                                   \
  template                                                             \
  IrreduciblePolynomialGenerator<Base>::IrreduciblePolynomialGenerator(   \
      std::istream& inputStream);                                      \
  template                                                             \
  const std::vector<GaloisFieldPolynomial<Base>>&                         \
  IrreduciblePolynomialGenerator<Base>::operator()(const size_t num);     \
  template                                                             \
  GaloisFieldPolynomial<2>                                             \
  IrreduciblePolynomialGenerator<Base>::GetNext();                        \
  template                                                             \
  void                                                                 \
  IrreduciblePolynomialGenerator<Base>::Save(std::ostream& output) const; \
  template                                                             \
  GaloisFieldPolynomial<Base>                                             \
  IrreduciblePolynomialGenerator<Base>::FindIrreduciblePolynomial(        \
      size_t& seed) const;

TEMPLATE_INSTANTIATION(2);
} // namespace gns
