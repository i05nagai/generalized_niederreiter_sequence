#include "gf/IrreduciblePolynomial.h"
#include <iostream>
#include <fstream>

void calc_iterative_irreducible_polynomial()
{
  std::ofstream writingFile;
  writingFile.open("irreducible_polynomia_gf2.txt", std::ios::out);

  const size_t num = 200;
  gf::IrreduciblePolynomialGenerator<2> generator;
  for (size_t i = 0; i < num; ++i) {
    const gf::Polynomial<2>& actual = generator.getNext();
    writingFile 
      << actual.toString(gf::EnumPolynomialExpression::INTEGER)
      << std::endl;;
  }
}

int main(int argc, char const* argv[])
{
  if (argc > 1) {
    if (argv) {
    }
  }
  calc_iterative_irreducible_polynomial();
  return 0;
}
