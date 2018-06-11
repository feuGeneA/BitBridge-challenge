#include <benchmark/benchmark.h>

#include "listutil.h"
#include "node.h"

template <size_t n>
static void benchmarkDeepCopy(benchmark::State& state)
{
    node* list = createList(n);
    for (auto _ : state)
    {
        node * copy = deepCopy(list);

        state.PauseTiming();

        deleteList(copy);

        state.ResumeTiming();
    }
    deleteList(list);
}

BENCHMARK_TEMPLATE(benchmarkDeepCopy, 1);
BENCHMARK_TEMPLATE(benchmarkDeepCopy, 10);
BENCHMARK_TEMPLATE(benchmarkDeepCopy, 100);
BENCHMARK_TEMPLATE(benchmarkDeepCopy, 1000);
BENCHMARK_TEMPLATE(benchmarkDeepCopy, 10000);
//BENCHMARK_TEMPLATE(benchmarkDeepCopy, 100000);
//BENCHMARK_TEMPLATE(benchmarkDeepCopy, 1000000);
