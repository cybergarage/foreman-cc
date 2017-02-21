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
#define FORMANCC_BENCHMARK_METRICS_COUNT 1000
#define FORMANCC_BENCHMARK_METRICS_NAME_PREFIX "name"

static void ForemanMemmemStoreInsert(benchmark::State& state) {
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR = state.range(0);
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC = (60 * 60 * FORMANCC_BENCHMARK_RETENSION_PERIOD_HOUR);
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_COUNT = (FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC / FORMANCC_BENCHMARK_RETENSION_INTERVAL);
  
  while (state.KeepRunning()) {
    Foreman::MemStore *memStore = new Foreman::RingMapStore();
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
    
    // Initialize memmemStore
    
    memStore->setRetentionInterval(FORMANCC_BENCHMARK_RETENSION_INTERVAL);
    memStore->setRetentionPeriod(FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC);
    
    for (std::shared_ptr<Foreman::Metric> m : metrics) {
      memStore->addMetric(*m);
    }
    
    memStore->realloc();
    
    // Insert metrics

    time_t beginTs = time(NULL);
    time_t metricTs = beginTs;
    for (size_t n = 0; n < FORMANCC_BENCHMARK_RETENSION_PERIOD_COUNT; n++) {
      Foreman::Metrics values;
      for (std::shared_ptr<Foreman::Metric> m : metrics) {
        std::shared_ptr<Foreman::Metric> value = std::shared_ptr<Foreman::Metric>(new Foreman::Metric(*m));
        value->timestamp = metricTs;
        value->value = n;
        values.push_back(value);
      }
      memStore->addValues(values);
      metricTs += FORMANCC_BENCHMARK_RETENSION_INTERVAL;
    }
    time_t endTs = metricTs;
    
    // Get metrics
    
    for (std::shared_ptr<Foreman::Metric> m : metrics) {
      std::shared_ptr<Foreman::MetricValue> values = nullptr;
      size_t valueCnt = 0;
      memStore->getValues(*m, beginTs, endTs, FORMANCC_BENCHMARK_RETENSION_INTERVAL, values, valueCnt);
    }
 
    memStore->close();
    
    delete memStore;
  }
}

BENCHMARK(ForemanMemmemStoreInsert)->Arg(1)->Arg(2)->Arg(4)->Arg(8)->Arg(12)->Arg(24);

BENCHMARK_MAIN();
