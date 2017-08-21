#include <benchmark/benchmark.h>
#include "gns/galois_field.h"
#include "gns/galois_field_operator.h"


#define BenchmarkGaloisFieldOperator(op, op_name)                        \
  static void BenchmarkGaloisFieldOperator ## op_name (                  \
      benchmark::State& state)                                           \
  {                                                                      \
    while(state.KeepRunning()) {                                         \
      for (int i = 0; i < 2; ++i) {                                      \
        for (int j = 0; j < 2; ++j) {                                    \
          const gns::GaloisField<2> e1(i);                                \
          const gns::GaloisField<2> e2(j);                                \
          benchmark::DoNotOptimize(e1 op e2);                            \
        }                                                                \
      }                                                                  \
      for (int i = 0; i < 4; ++i) {                                      \
        for (int j = 0; j < 4; ++j) {                                    \
          const gns::GaloisField<4> e1(i);                                \
          const gns::GaloisField<4> e2(j);                                \
          benchmark::DoNotOptimize(e1 op e2);                            \
        }                                                                \
      }                                                                  \
      for (int i = 0; i < 16; ++i) {                                     \
        for (int j = 0; j < 16; ++j) {                                   \
          const gns::GaloisField<16> e1(i);                               \
          const gns::GaloisField<16> e2(j);                               \
          benchmark::DoNotOptimize(e1 op e2);                            \
        }                                                                \
      }                                                                  \
    }                                                                    \
  }                                                                      \
  BENCHMARK(BenchmarkGaloisFieldOperator ## op_name);

BenchmarkGaloisFieldOperator(+, Plus);
BenchmarkGaloisFieldOperator(-, Sub);
BenchmarkGaloisFieldOperator(*, Mult);
BenchmarkGaloisFieldOperator(/, Div);

#define BenchmarkGaloisFieldOperatorFunc(op, op_name)         \
  static void BenchmarkGaloisFieldOperatorFunc ## op_name (   \
      benchmark::State& state)                                \
  {                                                           \
    using namespace gns;                                       \
    while(state.KeepRunning()) {                              \
      for (int i = 0; i < 2; ++i) {                           \
        for (int j = 0; j < 2; ++j) {                         \
          benchmark::DoNotOptimize( op <2>(i, j));            \
        }                                                     \
      }                                                       \
      for (int i = 0; i < 4; ++i) {                           \
        for (int j = 0; j < 4; ++j) {                         \
          benchmark::DoNotOptimize( op <4>(i, j));            \
        }                                                     \
      }                                                       \
      for (int i = 0; i < 16; ++i) {                          \
        for (int j = 0; j < 16; ++j) {                        \
          benchmark::DoNotOptimize( op <16>(i, j));           \
        }                                                     \
      }                                                       \
    }                                                         \
  }                                                           \
  BENCHMARK(BenchmarkGaloisFieldOperatorFunc ## op_name);

BenchmarkGaloisFieldOperatorFunc(add, Plus);
BenchmarkGaloisFieldOperatorFunc(sub, Sub);
BenchmarkGaloisFieldOperatorFunc(mult, Mult);
BenchmarkGaloisFieldOperatorFunc(div, Div);

BENCHMARK_MAIN();
