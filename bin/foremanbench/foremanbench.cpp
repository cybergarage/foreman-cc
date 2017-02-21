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
#include <string>
#include <sstream>

#include <benchmark/benchmark.h>
#include <foreman/MemStore.h>

#define FORMANCC_BENCHMARK_RETENSION_INTERVAL 60
#define FORMANCC_BENCHMARK_METRICS_COUNT 10000
#define FORMANCC_BENCHMARK_METRICS_NAME_PREFIX "name"

bool ForemanInitializeMemStore(Foreman::MemStore *memStore, size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR) {
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC = (60 * 60 * FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR);
  
  memStore->open();
  
  // Initialize metrics
  
  Foreman::Metrics metrics;
  std::ostringstream s;
  for (size_t n = 0; n < FORMANCC_BENCHMARK_METRICS_COUNT; n++) {
    s << FORMANCC_BENCHMARK_METRICS_NAME_PREFIX << n;
    std::shared_ptr<Foreman::Metric> m = std::shared_ptr<Foreman::Metric>(new Foreman::Metric());
    m->name = s.str();
    metrics.push_back(m);
  }
  
  memStore->setRetentionInterval(FORMANCC_BENCHMARK_RETENSION_INTERVAL);
  memStore->setRetentionPeriod(FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC);
  
  for (std::shared_ptr<Foreman::Metric> m : metrics) {
    memStore->addMetric(*m);
  }
  
  if (!memStore->realloc())
    return false;
  
  return true;
}

bool ForemanInsertMemStore(Foreman::MemStore *memStore, size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR, time_t &beginTs, time_t &endTs) {
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC = (60 * 60 * FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR);
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_COUNT = (FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC / FORMANCC_BENCHMARK_RETENSION_INTERVAL);
  
  beginTs = time(NULL);
  time_t metricTs = beginTs;
  for (size_t n = 0; n < FORMANCC_BENCHMARK_RETENSION_PERIOD_COUNT; n++) {
    Foreman::Metrics values;
    for (std::shared_ptr<Foreman::Metric> m : memStore->getMetrics()) {
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

bool ForemanReadMemStore(Foreman::MemStore *memStore, size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR, time_t beginTs, time_t endTs) {
  for (std::shared_ptr<Foreman::Metric> m : memStore->getMetrics()) {
    std::shared_ptr<Foreman::MetricValue> values = nullptr;
    size_t valueCnt = 0;
    if (!memStore->getValues(*m, beginTs, endTs, FORMANCC_BENCHMARK_RETENSION_INTERVAL, values, valueCnt))
      return false;
  }
  return true;
}

bool ForemanFinalizeMemStore(Foreman::MemStore *memStore) {
  memStore->close();
  delete memStore;
  return true;
}

template <class MemStoreClass> void ForemanMemStoreWrite(benchmark::State& state) {
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR = state.range(0);
  time_t beginTs = 0, endTs = 0;
  
  while (state.KeepRunning()) {
    state.PauseTiming();
    Foreman::MemStore *memStore = new MemStoreClass();
    if (!ForemanInitializeMemStore(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR)) {
      state.SkipWithError("Couldn't initialize MemStore !!");
    }
    state.ResumeTiming();
    if (!ForemanInsertMemStore(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR, beginTs, endTs)) {
      state.SkipWithError("Couldn't insert records to MemStore !!");
    }
    state.PauseTiming();
    if (!ForemanFinalizeMemStore(memStore)) {
      state.SkipWithError("Couldn't finalize MemStore !!");
    }
  }
}

template <class MemStoreClass> void ForemanMemStoreRead(benchmark::State& state) {
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR = state.range(0);
  time_t beginTs = 0, endTs = 0;
  
  while (state.KeepRunning()) {
    state.PauseTiming();
    Foreman::MemStore *memStore = new MemStoreClass();
    if (!ForemanInitializeMemStore(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR)) {
      state.SkipWithError("Couldn't initialize MemStore !!");
    }
    if (!ForemanInsertMemStore(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR, beginTs, endTs)) {
      state.SkipWithError("Couldn't insert records to MemStore !!");
    }
    state.ResumeTiming();
    if (!ForemanReadMemStore(memStore, FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR, beginTs, endTs)) {
      state.SkipWithError("Couldn't read records from MemStore !!");
    }
    state.PauseTiming();
    if (!ForemanFinalizeMemStore(memStore)) {
      state.SkipWithError("Couldn't finalize MemStore !!");
    }
  }
}

BENCHMARK_TEMPLATE(ForemanMemStoreWrite, Foreman::RingMapStore)->Arg(1)->Arg(2)->Arg(4)->Arg(8)->Arg(12)->Arg(24);
BENCHMARK_TEMPLATE(ForemanMemStoreRead, Foreman::RingMapStore)->Arg(1)->Arg(2)->Arg(4)->Arg(8)->Arg(12)->Arg(24);

BENCHMARK_MAIN();
