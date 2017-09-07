#include "gns/sequence_sobol.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>

/**
  Calculate two dim points with Generalized Niederreiter Sequence (Sobol)
  with base 2, 4, 16.
 */
template <int Base>
std::vector<std::vector<double>> CalculateSobol(const size_t num_point)
{
  gns::Sobol<Base> sobol(2);
  std::vector<std::vector<double>> data(num_point);
  for (size_t i = 0; i < num_point; ++i) {
      std::unique_ptr<double[]> point = sobol.Next();
      data[i] = {point[0], point[1]};
  }
  return data;
}

/**
  Calculate two dim points with MC.
 */
std::vector<std::vector<double>> CalculatePseudoRandom(const size_t num_point)
{
  std::mt19937 engine(0);
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  dist(engine);
  std::vector<std::vector<double>> data(num_point);
  for (size_t i = 0; i < num_point; ++i) {
      const double p0 = dist(engine);
      const double p1 = dist(engine);
      data[i] = {p0, p1};
  }
  return data;
}

/**
  Display points.
 */
std::string DisplayString(const std::string label,
                          const std::vector<std::vector<double>>& points)
{
  std::ostringstream text;
  text
    << std::setw(5)
    << "i,"
    << std::setw(15)
    << label << " x,"
    << std::setw(15)
    << label << " y"
    << std::endl;

  for (size_t i = 0; i < points.size(); ++i) {
    text
      << std::fixed
      << std::setprecision(8)
      << std::setw(5)
      << i + 1
      << ","
      << std::setw(15)
      << points[i][0]
      << ","
      << std::setw(15)
      << points[i][1]
      << std::endl;
  }
  return text.str();
}

void WriteToFile(const std::string& filename, const std::string& text)
{
  std::ofstream file;
  file.open(filename);
  file << text;
  file.close();
}

int main(int argc, char const* argv[])
{
  const size_t num_point = 1000;
  std::vector<std::vector<double>> qmc_base2 = CalculateSobol<2>(num_point);
  std::vector<std::vector<double>> qmc_base4 = CalculateSobol<4>(num_point);
  std::vector<std::vector<double>> qmc_base16 = CalculateSobol<16>(num_point);
  std::vector<std::vector<double>> mc = CalculatePseudoRandom(num_point);

  const std::string text_qmc2 = DisplayString("QMC2", qmc_base2);
  WriteToFile("qmc2", text_qmc2);
  std::cout << text_qmc2 << std::endl;
  const std::string text_qmc4 = DisplayString("QMC4", qmc_base4);
  WriteToFile("qmc4", text_qmc4);
  std::cout << text_qmc4 << std::endl;
  const std::string text_qmc16 = DisplayString("QMC16", qmc_base16);
  WriteToFile("qmc16", text_qmc16);
  std::cout << text_qmc16 << std::endl;
  const std::string text_mc = DisplayString("MC", mc);
  WriteToFile("mc", text_mc);
  std::cout << text_mc << std::endl;
  return 0;
}
