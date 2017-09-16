#include "gns/irreducible_polynomial.h"
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

namespace gns {
template <int Base>
IrreduciblePolynomialGenerator<Base>::IrreduciblePolynomialGenerator()
    : seed_(Base), irreducibles_(0) {
    }

template <int Base>
IrreduciblePolynomialGenerator<Base>::IrreduciblePolynomialGenerator(
    std::istream& input_stream)
  : seed_(Base),
  irreducibles_(0) {
  if (input_stream.fail()) {
    throw std::runtime_error("Read file error!");
  }
  std::unique_ptr<char[]> line(new char[256]);
  // read from input stream
  while (input_stream.getline(line.get(), 256)) {
    irreducibles_.emplace_back(MakeGaloisFieldPolynomial<Base>(line.get()));
  }
  // set last polynomial as seed
  seed_ = std::stoul(
      irreducibles_.back().ToString(EnumPolynomialExpression::INTEGER));
}

template <int Base>
const std::vector<GaloisFieldPolynomial<Base>>&
IrreduciblePolynomialGenerator<Base>::operator()(const size_t num) {
  const size_t num_iter = num - irreducibles_.size();

  // if num irreducible polynomials has already founded
  if (num_iter <= 0) {
    return irreducibles_;
  }

  // find num irredusible polymonials
  for (size_t i = 0; i < num_iter; ++i) {
    irreducibles_.push_back(this->FindIrreduciblePolynomial());
  }

  return irreducibles_;
}

template <int Base>
GaloisFieldPolynomial<Base> IrreduciblePolynomialGenerator<Base>::GetNext() {
  irreducibles_.emplace_back(this->FindIrreduciblePolynomial());
  return irreducibles_.back();
}

template <int Base>
void IrreduciblePolynomialGenerator<Base>::Save(
    std::ostream& output, const std::string delimiter) const {
  for (size_t i = 0; i < irreducibles_.size(); ++i) {
    output << irreducibles_[i].ToString(EnumPolynomialExpression::INTEGER)
           << delimiter
           << std::endl;
  }
}

template <int Base>
GaloisFieldPolynomial<Base>
IrreduciblePolynomialGenerator<Base>::ConvertToPolynomial(
    const size_t num) const {
  std::pair<size_t, std::unique_ptr<GaloisField<Base>[]>> result =
      CalculateBaseAdic<Base>(num);
  const size_t degree = (result.first - 1);
  return GaloisFieldPolynomial<Base>(degree, std::move(result.second));
}

template <int Base>
GaloisFieldPolynomial<Base>
IrreduciblePolynomialGenerator<Base>::FindIrreduciblePolynomial() {
  constexpr size_t max_loop = 5000;
  // check irreducibility from seed to seed + maxLoop
  for (size_t i = seed_; i < seed_ + max_loop; ++i) {
    bool is_reducible = false;
    GaloisFieldPolynomial<Base> polynomial = this->ConvertToPolynomial(i);

    // check dividable or not
    for (size_t j = 0; j < irreducibles_.size(); ++j) {
      const GaloisFieldPolynomial<Base>& divisor = irreducibles_[j];
      std::pair<GaloisFieldPolynomial<Base>, GaloisFieldPolynomial<Base>>
          result = EuclideanDivision(polynomial, divisor);
      const GaloisFieldPolynomial<Base>& residual = result.second;
      // dividable
      if (residual.IsZero()) {
        is_reducible = true;
        break;
      }
    }
    // irreducible
    if (!is_reducible) {
      seed_ = i + 1;
      return polynomial;
    }
  }
  // not found
  return GaloisFieldPolynomial<Base>(0);
}

/*--------------------------------------------------------------------------
 * free functions
 *------------------------------------------------------------------------*/
template <int Base>
GaloisFieldPolynomial<Base> MakeGaloisFieldPolynomial(const size_t data) {
  std::pair<size_t, std::unique_ptr<GaloisField<Base>[]>> degree_and_coeffs =
      CalculateBaseAdic<Base>(data);
  const size_t& degree = (degree_and_coeffs.first - 1);
  return GaloisFieldPolynomial<Base>(degree,
                                     std::move(degree_and_coeffs.second));
}

template <int Base>
GaloisFieldPolynomial<Base> MakeGaloisFieldPolynomial(const char* str_data) {
  size_t data = atoi(str_data);
  return MakeGaloisFieldPolynomial<Base>(data);
}

}  // namespace gns

namespace gns {
#define TEMPLATE_INSTANTIATION(Base)                                       \
  template IrreduciblePolynomialGenerator<                                 \
      Base>::IrreduciblePolynomialGenerator();                             \
  template IrreduciblePolynomialGenerator<                                 \
      Base>::IrreduciblePolynomialGenerator(std::istream& inputStream);    \
  template const std::vector<GaloisFieldPolynomial<Base>>&                 \
  IrreduciblePolynomialGenerator<Base>::operator()(const size_t num);      \
  template GaloisFieldPolynomial<Base>                                     \
  IrreduciblePolynomialGenerator<Base>::GetNext();                         \
  template void IrreduciblePolynomialGenerator<Base>::Save(                \
      std::ostream& output, const std::string delimiter) const;            \
  template GaloisFieldPolynomial<Base>                                     \
  IrreduciblePolynomialGenerator<Base>::FindIrreduciblePolynomial();       \
  template \
  GaloisFieldPolynomial<Base> MakeGaloisFieldPolynomial(const char* str_data);

TEMPLATE_INSTANTIATION(2);
TEMPLATE_INSTANTIATION(4);
TEMPLATE_INSTANTIATION(16);
}  // namespace gns
