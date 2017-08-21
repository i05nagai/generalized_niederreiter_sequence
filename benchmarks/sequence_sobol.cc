#include "benchmarks/sequence_sobol.h"
#include <benchmark/benchmark.h>
#include <cmath>
#include <iomanip>
#include <random>

static double EstimatePiSobol(const size_t num_point)
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

static void BenchmarkSobol(benchmark::State& state)
{
  while(state.KeepRunning()) {
    benchmark::DoNotOptimize(EstimatePiSobol(state.range(0)));
  }
}
BENCHMARK(BenchmarkSobol)
  ->Arg(100)
  ->Arg(1000)
  ->Arg(10000);

static double EstimatePiMC(const size_t num_point)
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

static void BenchmarkMonteCarlo(benchmark::State& state)
{
  while(state.KeepRunning()) {
    benchmark::DoNotOptimize(EstimatePiMC(state.range(0)));
  }
}
BENCHMARK(BenchmarkMonteCarlo)
  ->Arg(100)
  ->Arg(1000)
  ->Arg(10000);

BENCHMARK_MAIN();
