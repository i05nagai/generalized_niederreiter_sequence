#include "gns/sequence_sobol.h"
#include <cmath>
#include <iomanip>
#include <random>

/**
  Estimate PI with QMC using Generalized Niederreiter Sequence (Sobol)
  with base 2, 4, 16.
 */
template <int Base>
double EstimatePiQMC(const size_t num_point)
{
  gns::Sobol<Base> sobol(2);
  size_t num_inner_point = 0;
  for (size_t i = 0; i < num_point; ++i) {
      std::unique_ptr<double[]> point = sobol.Next();
      const double r = point[0] * point[0] + point[1] * point[1];
      if (r <= 1.0) {
        ++num_inner_point;
      }
  }
  return 4.0 * (num_inner_point / static_cast<double>(num_point));
}

/**
  Estimate PI with MC.
 */
double EstimatePiMC(const size_t num_point)
{
  std::mt19937 engine(0);
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  dist(engine);
  size_t num_inner_point = 0;
  for (size_t i = 0; i < num_point; ++i) {
      const double p0 = dist(engine);
      const double p1 = dist(engine);
      const double r = p0 * p0 + p1 * p1;
      if (r <= 1.0) {
        ++num_inner_point;
      }
  }
  return 4.0 * (num_inner_point / static_cast<double>(num_point));
}

/**
  Display convergence to true PI.
 */
void Display(
    const std::vector<size_t>& data,
    const std::vector<double>& qmc_base2,
    const std::vector<double>& qmc_base4,
    const std::vector<double>& qmc_base16,
    const std::vector<double>& mc,
    const double true_value)
{
  std::cout
    << std::setw(15)
    << "data"
    << std::setw(15)
    << "QMC2"
    << std::setw(15)
    << "QMC4"
    << std::setw(15)
    << "QMC16"
    << std::setw(15)
    << "MC"
    << std::setw(15)
    << "diff QMC2"
    << std::setw(15)
    << "diff QMC4"
    << std::setw(15)
    << "diff QMC16"
    << std::setw(15)
    << "diff MC"
    << std::endl;

  for (size_t i = 0; i < data.size(); ++i) {
    std::cout
      << std::fixed
      << std::setprecision(8)
      << std::setw(15)
      << data[i]
      << std::setw(15)
      << qmc_base2[i]
      << std::setw(15)
      << qmc_base4[i]
      << std::setw(15)
      << qmc_base16[i]
      << std::setw(15)
      << mc[i]
      << std::setw(15)
      << std::abs(qmc_base2[i] - true_value)
      << std::setw(15)
      << std::abs(qmc_base4[i] - true_value)
      << std::setw(15)
      << std::abs(qmc_base16[i] - true_value)
      << std::setw(15)
      << std::abs(mc[i] - true_value)
      << std::endl;
  }
}


int main(int argc, char const* argv[])
{
  constexpr double PI = 3.14159265358979323846;
  std::vector<size_t> data = {
    100, 1000, 10000, 100000
  };
  std::vector<double> qmc_base2(data.size());
  std::transform(data.begin(), data.end(), qmc_base2.begin(), EstimatePiQMC<2>);
  std::vector<double> qmc_base4(data.size());
  std::transform(data.begin(), data.end(), qmc_base4.begin(), EstimatePiQMC<4>);
  std::vector<double> qmc_base16(data.size());
  std::transform(data.begin(), data.end(), qmc_base16.begin(), EstimatePiQMC<16>);
  std::vector<double> mc(data.size());
  std::transform(data.begin(), data.end(), mc.begin(), EstimatePiMC);

  Display(data, qmc_base2, qmc_base4, qmc_base16, mc, PI);
  return 0;
}
