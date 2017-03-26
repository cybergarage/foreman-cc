/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <benchmark/benchmark.h>

#include "BenchmarkController.h"

#define FORMANCC_BENCHMARK_RETENSION_INTERVAL 60
#define FORMANCC_BENCHMARK_METRICS_COUNT 1000
#define FORMANCC_BENCHMARK_METRICS_READ_COUNT 100

template <class MemStoreClass>
void ForemanMemStoreWrite(benchmark::State& state)
{
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR = state.range(0);
  time_t beginTs = 0, endTs = 0;

  while (state.KeepRunning()) {
    state.PauseTiming();

    Foreman::BenchmarkController benchmark;
    benchmark.setRetentionIntervel(FORMANCC_BENCHMARK_RETENSION_INTERVAL);
    benchmark.setMetricsCount(FORMANCC_BENCHMARK_METRICS_COUNT);

    Foreman::MemStore* memStore = new MemStoreClass();

    if (benchmark.initialize(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR)) {
      state.SkipWithError("Couldn't initialize MemStore !!");
    }

    state.ResumeTiming();

    if (!benchmark.insertRecords(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR, beginTs, endTs)) {
      state.SkipWithError("Couldn't insert records to MemStore !!");
    }

    state.PauseTiming();

    if (benchmark.finalize(memStore)) {
      state.SkipWithError("Couldn't finalize MemStore !!");
    }

    delete memStore;
  }
}

template <class MemStoreClass>
void ForemanMemStoreRead(benchmark::State& state)
{
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR = state.range(0);
  time_t beginTs = 0, endTs = 0;

  while (state.KeepRunning()) {
    state.PauseTiming();

    Foreman::BenchmarkController benchmark;
    benchmark.setRetentionIntervel(FORMANCC_BENCHMARK_RETENSION_INTERVAL);
    benchmark.setMetricsCount(FORMANCC_BENCHMARK_METRICS_COUNT);

    Foreman::MemStore* memStore = new MemStoreClass();

    if (benchmark.initialize(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR)) {
      state.SkipWithError("Couldn't initialize MemStore !!");
    }

    if (!benchmark.insertRecords(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR, beginTs, endTs)) {
      state.SkipWithError("Couldn't insert records to MemStore !!");
    }

    state.ResumeTiming();

    if (!benchmark.readRecords(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR, beginTs, endTs, FORMANCC_BENCHMARK_METRICS_READ_COUNT)) {
      state.SkipWithError("Couldn't read records from MemStore !!");
    }
    state.PauseTiming();

    if (benchmark.finalize(memStore)) {
      state.SkipWithError("Couldn't finalize MemStore !!");
    }

    delete memStore;
  }
}

////////////////////////////////////////////////
// RingMapStor
////////////////////////////////////////////////

BENCHMARK_TEMPLATE(ForemanMemStoreWrite, Foreman::RingMapStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(12)
    ->Arg(24);
BENCHMARK_TEMPLATE(ForemanMemStoreRead, Foreman::RingMapStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(12)
    ->Arg(24);

////////////////////////////////////////////////
// NarrowTableStore
////////////////////////////////////////////////

BENCHMARK_TEMPLATE(ForemanMemStoreWrite, Foreman::NarrowTableStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(12)
    ->Arg(24);
BENCHMARK_TEMPLATE(ForemanMemStoreRead, Foreman::NarrowTableStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(12)
    ->Arg(24);

////////////////////////////////////////////////
// MatrixStore
////////////////////////////////////////////////

BENCHMARK_TEMPLATE(ForemanMemStoreWrite, Foreman::MatrixStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(12)
    ->Arg(24);

BENCHMARK_TEMPLATE(ForemanMemStoreRead, Foreman::MatrixStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(12)
    ->Arg(24);

////////////////////////////////////////////////
// TSmapStore
////////////////////////////////////////////////

BENCHMARK_TEMPLATE(ForemanMemStoreWrite, Foreman::TSmapStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(12)
    ->Arg(24);

BENCHMARK_TEMPLATE(ForemanMemStoreRead, Foreman::TSmapStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(12)
    ->Arg(24);

BENCHMARK_MAIN();
