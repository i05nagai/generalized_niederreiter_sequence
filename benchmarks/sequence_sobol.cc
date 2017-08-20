#include "benchmarks/sequence_sobol.h"
#include <benchmark/benchmark.h>

static void BenchmarkSobol(benchmark::State& state)
{
  while(state.KeepRunning()) {
    gns::Sobol<2> sobol(2);
    size_t num_inner_point = 0;
    const size_t num_point = 1000;
    for (size_t i = 0; i < num_point; ++i) {
        std::unique_ptr<double[]> point = sobol.Next();
        const double r = point[0] * point[0] + point[1] * point[1];
        if (r <= 1.0) {
          ++num_inner_point;
        }
    }
    benchmark::DoNotOptimize(4.0 * (num_inner_point / static_cast<double>(num_point)));
  }
}
BENCHMARK(BenchmarkSobol);

BENCHMARK_MAIN();
