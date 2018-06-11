#include <benchmark/benchmark.h>

#include "nodelist.h"

template <size_t n>
static void benchmarkDeepCopy(benchmark::State& state)
{
    NodeList list(n);
    for (auto _ : state)
    {
        NodeList *deepCopy = new NodeList(list);

        state.PauseTiming();

        delete deepCopy;

        state.ResumeTiming();
    }
}

BENCHMARK_TEMPLATE(benchmarkDeepCopy, 1);
BENCHMARK_TEMPLATE(benchmarkDeepCopy, 10);
BENCHMARK_TEMPLATE(benchmarkDeepCopy, 100);
BENCHMARK_TEMPLATE(benchmarkDeepCopy, 1000);
BENCHMARK_TEMPLATE(benchmarkDeepCopy, 10000);
//BENCHMARK_TEMPLATE(benchmarkDeepCopy, 100000);
//BENCHMARK_TEMPLATE(benchmarkDeepCopy, 1000000);
