#include "gns/sequence_sobol.h"
#include "gns/sequence_simple_sobol.h"
#include <benchmark/benchmark.h>
#include <cmath>
#include <iomanip>
#include <random>

/*--------------------------------------------------------------------------
 * Sobol
 *------------------------------------------------------------------------*/
template <int Base>
static double EstimatePiSobol(const size_t num_point)
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

static void BenchmarkSobolBase2(benchmark::State& state)
{
  while(state.KeepRunning()) {
    benchmark::DoNotOptimize(EstimatePiSobol<2>(state.range(0)));
  }
}
BENCHMARK(BenchmarkSobolBase2)
  ->Arg(100)
  ->Arg(1000)
  ->Arg(10000);

static void BenchmarkSobolBase4(benchmark::State& state)
{
  while(state.KeepRunning()) {
    benchmark::DoNotOptimize(EstimatePiSobol<4>(state.range(0)));
  }
}

BENCHMARK(BenchmarkSobolBase4)
  ->Arg(100)
  ->Arg(1000)
  ->Arg(10000);

static void BenchmarkSobolBase16(benchmark::State& state)
{
  while(state.KeepRunning()) {
    benchmark::DoNotOptimize(EstimatePiSobol<16>(state.range(0)));
  }
}

BENCHMARK(BenchmarkSobolBase16)
  ->Arg(100)
  ->Arg(1000)
  ->Arg(10000);

/*--------------------------------------------------------------------------
 * Sobol Gray Map
 *------------------------------------------------------------------------*/
template <int Base>
static double EstimatePiSobolGrayMap(const size_t num_point)
{
  gns::SobolGrayMap<Base> sobol(2);
  size_t num_inner_point = 0;
  for (size_t i = 0; i < num_point; ++i) {
      const std::unique_ptr<double[]>& point = sobol.Next();
      const double r = point[0] * point[0] + point[1] * point[1];
      if (r <= 1.0) {
        ++num_inner_point;
      }
  }
  return 4.0 * (num_inner_point / static_cast<double>(num_point));
}

static void BenchmarkSobolGrayMapBase2(benchmark::State& state)
{
  while(state.KeepRunning()) {
    benchmark::DoNotOptimize(EstimatePiSobolGrayMap<2>(state.range(0)));
  }
}
BENCHMARK(BenchmarkSobolGrayMapBase2)
  ->Arg(100)
  ->Arg(1000)
  ->Arg(10000);

static void BenchmarkSobolGrayMapBase4(benchmark::State& state)
{
  while(state.KeepRunning()) {
    benchmark::DoNotOptimize(EstimatePiSobolGrayMap<4>(state.range(0)));
  }
}
BENCHMARK(BenchmarkSobolGrayMapBase4)
  ->Arg(100)
  ->Arg(1000)
  ->Arg(10000);

static void BenchmarkSobolGrayMapBase16(benchmark::State& state)
{
  while(state.KeepRunning()) {
    benchmark::DoNotOptimize(EstimatePiSobolGrayMap<16>(state.range(0)));
  }
}
BENCHMARK(BenchmarkSobolGrayMapBase16)
  ->Arg(100)
  ->Arg(1000)
  ->Arg(10000);

/*--------------------------------------------------------------------------
 * Simple Sobol Gray Map
 *------------------------------------------------------------------------*/
template <int Base>
static double EstimatePiSimpleSobolGrayMap(const size_t num_point)
{
  gns::SimpleSobolGrayMap sobol(2);
  size_t num_inner_point = 0;
  for (size_t i = 0; i < num_point; ++i) {
      const std::vector<double>& point = sobol.Next();
      const double r = point[0] * point[0] + point[1] * point[1];
      if (r <= 1.0) {
        ++num_inner_point;
      }
  }
  return 4.0 * (num_inner_point / static_cast<double>(num_point));
}

static void BenchmarkSimpleSobolGrayMapBase2(benchmark::State& state)
{
  while(state.KeepRunning()) {
    benchmark::DoNotOptimize(EstimatePiSimpleSobolGrayMap<2>(state.range(0)));
  }
}
BENCHMARK(BenchmarkSimpleSobolGrayMapBase2)
  ->Arg(100)
  ->Arg(1000)
  ->Arg(10000);

/*--------------------------------------------------------------------------
 * Monte Calro
 *------------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------------
 * main
 *------------------------------------------------------------------------*/
BENCHMARK_MAIN();
