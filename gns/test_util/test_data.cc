#include "gns/test_util/test_data.h"
#include <algorithm>
#include <vector>
#include "gns/test_util/random_number.h"

namespace gns {
namespace test_util {
std::vector<double> TestData::GetRandomNumbers(const size_t size) {
  static RandomNumber generator;

  std::vector<double> x(size);
  std::generate(x.begin(), x.end(), generator);
  return x;
}

template <int Base>
std::unique_ptr<GaloisField<Base>[]> TestData::GetRandomGaloisFieldArray(
    const size_t size) {
  std::vector<double> data = TestData::GetRandomNumbers(size);

  std::unique_ptr<GaloisField<Base>[]> result(new GaloisField<Base>[size]);
  std::transform(data.begin(), data.end(), result.get(), [&](double x) {
    return TestData::DoubleToGaloisField<Base>(x);
  });
  return result;
}

template <int Base>
std::unique_ptr<GaloisField<Base>[]> TestData::GetPolynomialCoefficients(
    const size_t degree) {
  std::unique_ptr<GaloisField<Base>[]> data =
      TestData::GetRandomGaloisFieldArray<Base>(degree + 1);
  if (data[degree] == 0) {
    data[degree] = GaloisField<Base>(1);
  }
  return data;
}

template <int Base>
gns::GaloisFieldPolynomial<Base> TestData::GetRandomPolynomial(
    const size_t degree) {
  std::unique_ptr<GaloisField<Base>[]> data =
      TestData::GetPolynomialCoefficients<Base>(degree);
  auto p = gns::GaloisFieldPolynomial<Base>(degree, std::move(data));
  return p;
}

template <int Base>
GaloisField<Base> TestData::DoubleToGaloisField(const double data) {
  return GaloisField<Base>(static_cast<size_t>(data * Base));
}

/*--------------------------------------------------------------------------
 * free function
 *------------------------------------------------------------------------*/
template <int Base>
std::unique_ptr<GaloisField<Base>[]> MakeGaloisFieldArray(
    std::initializer_list<unsigned int> data) {
  std::unique_ptr<GaloisField<Base>[]> expect(
      new GaloisField<Base>[data.size()]);
  std::copy(data.begin(), data.end(), expect.get());
  return expect;
}
}  // namespace test_util
}  // namespace gns

namespace gns {
namespace test_util {
#define TEMPLATE_INSTANTIATION(Base)                                           \
  template std::unique_ptr<GaloisField<Base>[]>                                \
  TestData::GetRandomGaloisFieldArray(const size_t size);                      \
  template std::unique_ptr<GaloisField<Base>[]>                                \
  TestData::GetPolynomialCoefficients(const size_t degree);                    \
  template gns::GaloisFieldPolynomial<Base> TestData::GetRandomPolynomial(     \
      const size_t degree);                                                    \
  template GaloisField<Base> TestData::DoubleToGaloisField(const double data); \
  template std::unique_ptr<GaloisField<Base>[]> MakeGaloisFieldArray(          \
      std::initializer_list<unsigned int> data);

TEMPLATE_INSTANTIATION(2);
TEMPLATE_INSTANTIATION(4);
TEMPLATE_INSTANTIATION(16);
#undef TEMPLATE_INSTANTIATION
}  // namespace test_util
}  // namespace gns
