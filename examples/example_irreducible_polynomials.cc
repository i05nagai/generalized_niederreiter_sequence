#include "gns/irreducible_polynomial.h"
#include <fstream>
#include <vector>

template <int Base>
void WriteIrreduciblePolynomial(
    const size_t num_irreducibles,
    std::string filename,
    const bool use_prepared_irreducibles)
{
    gns::IrreduciblePolynomialGenerator<Base> generator(
        use_prepared_irreducibles);

    std::vector<gns::GaloisFieldPolynomial<Base>> data
      = generator(num_irreducibles);

    std::ofstream file;
    file.open(filename);
    generator.Save(file, ",");
    file.close();
}

int main(int argc, char const* argv[])
{
  const size_t num_irreducibles = 500;
  WriteIrreduciblePolynomial<2>(
      num_irreducibles,
      "irreducible_polynomial_gf2.txt",
      false);
  WriteIrreduciblePolynomial<4>(
      num_irreducibles,
      "irreducible_polynomial_gf4.txt",
      false);
  WriteIrreduciblePolynomial<16>(
      num_irreducibles,
      "irreducible_polynomial_gf16.txt",
      false);

  return 0;
}
