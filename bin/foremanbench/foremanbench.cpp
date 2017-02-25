/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include <benchmark/benchmark.h>
#include <foreman/MemStore.h>

#include "BenchmarkController.h"

#define FORMANCC_BENCHMARK_RETENSION_INTERVAL 60
#define FORMANCC_BENCHMARK_METRICS_COUNT 1000
#define FORMANCC_BENCHMARK_METRICS_READ_COUNT 100

<<<<<<< HEAD
if (!memStore->realloc())
  return false;

return true;
}

bool ForemanInsertMemStore(Foreman::MemStore* memStore, size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR, time_t& beginTs, time_t& endTs)
{
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC = (60 * 60 * FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR);
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_COUNT = (FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC / FORMANCC_BENCHMARK_RETENSION_INTERVAL);

  beginTs = time(NULL);
  time_t metricTs = beginTs;
  for (size_t n = 0; n < FORMANCC_BENCHMARK_RETENSION_PERIOD_COUNT; n++) {
    Foreman::Metrics values;
    std::shared_ptr<std::vector<std::shared_ptr<Foreman::Metric> > > metrics = memStore->getMetrics();
    for (auto it = metrics->begin(); it != metrics->end(); ++it) {
      std::shared_ptr<Foreman::Metric> m = *it;
      std::shared_ptr<Foreman::Metric> value = std::shared_ptr<Foreman::Metric>(new Foreman::Metric(*m));
      value->timestamp = metricTs;
      value->value = n;
      values.push_back(value);
    }
    if (!memStore->addValues(values))
      return false;
    metricTs += FORMANCC_BENCHMARK_RETENSION_INTERVAL;
  }
  endTs = metricTs;
  return true;
}

bool ForemanReadMemStore(Foreman::MemStore* memStore, size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR, time_t beginTs, time_t endTs)
{
  std::shared_ptr<std::vector<std::shared_ptr<Foreman::Metric> > > metrics = memStore->getMetrics();
  for (size_t n = 0; n < FORMANCC_BENCHMARK_METRICS_READ_COUNT; n++) {
    for (auto it = metrics->begin(); it != metrics->end(); ++it) {
      std::shared_ptr<Foreman::Metric> m = *it;
      std::shared_ptr<Foreman::MetricValue> values = nullptr;
      size_t valueCnt = 0;
      if (!memStore->getValues(*m, beginTs, endTs, FORMANCC_BENCHMARK_RETENSION_INTERVAL, values, valueCnt))
        return false;
    }
  }
  return true;
}

bool ForemanFinalizeMemStore(Foreman::MemStore* memStore)
{
  memStore->close();
  delete memStore;
  return true;
}
=======
/*
 void setRetentionIntervel(time_t value) {retentionIntervel_ = value;}
 void setMetricsCount(time_t value) {metricsCount_ = value;}
 
 bool initialize(MemStore* memStore, size_t retensionPeriodHour);
 bool insertRecords(MemStore* memStore, size_t retensionPeriodHour, time_t& beginTs, time_t& endTs, size_t repeatCnt = 1);
 bool readRecords(MemStore* memStore, size_t retensionPeriodHour, time_t beginTs, time_t endTs, size_t repeatCnt = 1);
 bool finalize(MemStore* memStore);
*/
>>>>>>> 4efa0a16709a6e1ac94cdd6bb7ff74f2c24aa7a1

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

BENCHMARK_MAIN();
