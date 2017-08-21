#include "gns/sequence_sobol.h"
#include <cmath>
#include <iomanip>
#include <random>

double EstimatePiQMC(const size_t num_point)
{
  gns::Sobol<2> sobol(2);
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

void Display(
    const std::vector<size_t>& data,
    const std::vector<double>& qmc,
    const std::vector<double>& mc,
    const double true_value)
{
  std::cout
    << std::setw(15)
    << "data"
    << std::setw(15)
    << "QMC"
    << std::setw(15)
    << "MC"
    << std::setw(15)
    << "diff QMC"
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
      << qmc[i]
      << std::setw(15)
      << mc[i]
      << std::setw(15)
      << std::abs(qmc[i] - true_value)
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
  std::vector<double> pi_qmc(data.size());
  std::transform(data.begin(), data.end(), pi_qmc.begin(), EstimatePiQMC);
  std::vector<double> pi_mc(data.size());
  std::transform(data.begin(), data.end(), pi_mc.begin(), EstimatePiMC);

  Display(data, pi_qmc, pi_mc, PI);
  return 0;
}
