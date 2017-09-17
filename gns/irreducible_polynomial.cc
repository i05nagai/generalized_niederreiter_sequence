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
IrreduciblePolynomialGenerator<Base>::IrreduciblePolynomialGenerator(
    const bool use_prepared_irreducibles)
    : seed_(Base),
    irreducibles_(this->GetPreparedIrreducibles(use_prepared_irreducibles)) {
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
  constexpr size_t max_loop = 16 * 16 * 16 * 16 * 16 * 16;
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

template <int Base>
std::vector<GaloisFieldPolynomial<Base>>
IrreduciblePolynomialGenerator<Base>::GetPreparedIrreducibles(
    const bool use_prepared_irreducibles) const
{
  if (!use_prepared_irreducibles) {
    return std::vector<GaloisFieldPolynomial<Base>>(0);
  }
  const std::vector<int>& data = GetPreparedIrreduciblesData<Base>();
  std::vector<GaloisFieldPolynomial<Base>> irreducibles(data.size());
  std::transform(
      data.begin(),
      data.end(),
      irreducibles.begin(),
      [this](const int i){ 
        return this->ConvertToPolynomial(i);
      });
  return std::move(irreducibles);
}

/*--------------------------------------------------------------------------
 * free functions
 *------------------------------------------------------------------------*/
template <>
std::vector<int>
GetPreparedIrreduciblesData<2>()
{
  return {
#include "irreducible_polynomial_gf2.txt"
  };
}

template <>
std::vector<int>
GetPreparedIrreduciblesData<4>()
{
  return {
#include "irreducible_polynomial_gf4.txt"
  };
}

template <>
std::vector<int>
GetPreparedIrreduciblesData<16>()
{
  return {
#include "irreducible_polynomial_gf16.txt"
  };
}

template <int Base>
GaloisFieldPolynomial<Base> MakeGaloisFieldPolynomial(const char* str_data) {
  size_t data = atoi(str_data);
  std::pair<size_t, std::unique_ptr<GaloisField<Base>[]>> degree_and_coeffs =
      CalculateBaseAdic<Base>(data);
  const size_t& degree = (degree_and_coeffs.first - 1);
  return GaloisFieldPolynomial<Base>(
      degree, std::move(degree_and_coeffs.second));
}

}  // namespace gns

namespace gns {
#define TEMPLATE_INSTANTIATION(Base)                                       \
  template IrreduciblePolynomialGenerator<                                 \
      Base>::IrreduciblePolynomialGenerator();                             \
  template IrreduciblePolynomialGenerator<                                 \
      Base>::IrreduciblePolynomialGenerator(std::istream& inputStream);    \
  template IrreduciblePolynomialGenerator<                                 \
      Base>::IrreduciblePolynomialGenerator(                               \
          const bool use_prepared_irreducibles);                           \
  template const std::vector<GaloisFieldPolynomial<Base>>&                 \
  IrreduciblePolynomialGenerator<Base>::operator()(const size_t num);      \
  template void IrreduciblePolynomialGenerator<Base>::Save(                \
      std::ostream& output, const std::string delimiter) const;            \
  template std::vector<GaloisFieldPolynomial<Base>>                        \
  IrreduciblePolynomialGenerator<Base>::GetPreparedIrreducibles(           \
      const bool use_prepared_irreducibles) const;                         \
  template GaloisFieldPolynomial<Base>                                     \
  IrreduciblePolynomialGenerator<Base>::FindIrreduciblePolynomial();       \
  template \
  GaloisFieldPolynomial<Base> MakeGaloisFieldPolynomial(const char* str_data);

TEMPLATE_INSTANTIATION(2);
TEMPLATE_INSTANTIATION(4);
TEMPLATE_INSTANTIATION(16);
}  // namespace gns
