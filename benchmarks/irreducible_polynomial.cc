#include "benchmarks/irreducible_polynomial.h"

void calc_irreducible_polynomial()
{
  const size_t num = 100;
  gf::IrreduciblePolynomialGenerator<2> generator;
  const std::vector<gf::Polynomial<2>>& actual = generator(num);
  // to keep from optimization
  gf::Polynomial<2> copy = actual[num - 1];
}

void calc_iterative_irreducible_polynomial()
{
  const size_t num = 100;
  gf::IrreduciblePolynomialGenerator<2> generator;
  for (size_t i = 0; i < num; ++i) {
    const gf::Polynomial<2>& actual = generator.getNext();
    // to keep from optimization
    if (num >= i - 1) {
      gf::Polynomial<2> copy = actual;
    }
  }
}

int main(int argc, char const* argv[])
{
  if (argc > 1) {
    if (argv) {
    }
  }
  calc_irreducible_polynomial();
  calc_iterative_irreducible_polynomial();
  return 0;
}
