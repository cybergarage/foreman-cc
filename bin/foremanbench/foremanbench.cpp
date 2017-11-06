/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <benchmark/benchmark.h>

#include "BenchmarkController.h"

#define FORMANCC_BENCHMARK_RETENSION_INTERVAL 60
#define FORMANCC_BENCHMARK_METRICS_COUNT 1000
#define FORMANCC_BENCHMARK_METRICS_READ_COUNT 100
#define FORMANCC_BENCHMARK_RECORD_TYPE Foreman::BenchmarkControllerSporadicRecordType

template <class MemStoreClass>
void ForemanStoreWrite(benchmark::State& state)
{
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR = state.range(0);
  Foreman::BenchmarkControllerRecordType recordType = FORMANCC_BENCHMARK_RECORD_TYPE;
  time_t beginTs = 0, endTs = 0;

  while (state.KeepRunning()) {
    state.PauseTiming();

    Foreman::BenchmarkController benchmark;
    benchmark.setRetentionIntervel(FORMANCC_BENCHMARK_RETENSION_INTERVAL);
    benchmark.setMetricsCount(FORMANCC_BENCHMARK_METRICS_COUNT);

    Foreman::Metric::MemStore* memStore = new MemStoreClass();

    if (!benchmark.initialize(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR)) {
      state.SkipWithError("Couldn't initialize MemStore !!");
    }

    state.ResumeTiming();

    if (!benchmark.insertRecords(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR, beginTs, endTs, recordType)) {
      state.SkipWithError("Couldn't insert records to MemStore !!");
    }

    state.PauseTiming();

    if (!benchmark.finalize(memStore)) {
      state.SkipWithError("Couldn't finalize MemStore !!");
    }

    delete memStore;
  }
}

template <class MemStoreClass>
void ForemanStoreRead(benchmark::State& state)
{
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR = state.range(0);
  Foreman::BenchmarkControllerRecordType recordType = FORMANCC_BENCHMARK_RECORD_TYPE;
  time_t beginTs = 0, endTs = 0;

  while (state.KeepRunning()) {
    state.PauseTiming();

    Foreman::BenchmarkController benchmark;
    benchmark.setRetentionIntervel(FORMANCC_BENCHMARK_RETENSION_INTERVAL);
    benchmark.setMetricsCount(FORMANCC_BENCHMARK_METRICS_COUNT);

    Foreman::Metric::MemStore* memStore = new MemStoreClass();

    if (!benchmark.initialize(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR)) {
      state.SkipWithError("Couldn't initialize MemStore !!");
    }

    if (!benchmark.insertRecords(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR, beginTs, endTs, recordType)) {
      state.SkipWithError("Couldn't insert records to MemStore !!");
    }

    state.ResumeTiming();

    if (!benchmark.readRecords(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR, beginTs, endTs, FORMANCC_BENCHMARK_METRICS_READ_COUNT)) {
      state.SkipWithError("Couldn't read records from MemStore !!");
    }
    state.PauseTiming();

    if (!benchmark.finalize(memStore)) {
      state.SkipWithError("Couldn't finalize MemStore !!");
    }

    delete memStore;
  }
}

////////////////////////////////////////////////
// RingMapStor
////////////////////////////////////////////////

BENCHMARK_TEMPLATE(ForemanStoreWrite, Foreman::Metric::RingMapStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(16)
    ->Arg(32);
BENCHMARK_TEMPLATE(ForemanStoreRead, Foreman::Metric::RingMapStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(16)
    ->Arg(32);

////////////////////////////////////////////////
// NarrowTableStore
////////////////////////////////////////////////

BENCHMARK_TEMPLATE(ForemanStoreWrite, Foreman::Metric::NarrowTableStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(16)
    ->Arg(32);
BENCHMARK_TEMPLATE(ForemanStoreRead, Foreman::Metric::NarrowTableStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(16)
    ->Arg(32);

////////////////////////////////////////////////
// MatrixStore
////////////////////////////////////////////////

BENCHMARK_TEMPLATE(ForemanStoreWrite, Foreman::Metric::MatrixStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(16)
    ->Arg(32);

BENCHMARK_TEMPLATE(ForemanStoreRead, Foreman::Metric::MatrixStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(16)
    ->Arg(32);

////////////////////////////////////////////////
// TSmapStore
////////////////////////////////////////////////

BENCHMARK_TEMPLATE(ForemanStoreWrite, Foreman::Metric::BeringeiStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(16)
    ->Arg(32);

BENCHMARK_TEMPLATE(ForemanStoreRead, Foreman::Metric::BeringeiStore)
    ->Arg(1)
    ->Arg(4)
    ->Arg(8)
    ->Arg(16)
    ->Arg(32);

BENCHMARK_MAIN();
