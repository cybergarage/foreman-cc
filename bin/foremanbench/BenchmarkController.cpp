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

#include "BenchmarkController.h"

using namespace Foreman;

////////////////////////////////////////////////
// BenchmarkController
////////////////////////////////////////////////

BenchmarkController::BenchmarkController()
{
  retentionIntervel_ = FORMANCC_BENCHMARK_DEFAULT_RETENSION_INTERVAL;
  metricsCount_ = FORMANCC_BENCHMARK_DEFAULT_METRICS_COUNT;
}

BenchmarkController::~BenchmarkController()
{
}

////////////////////////////////////////////////
// initialize
////////////////////////////////////////////////

bool BenchmarkController::initialize(MemStore* memStore, size_t retensionPeriodHour)
{
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC = (60 * 60 * retensionPeriodHour);

  memStore->open();

  // Initialize metrics

  Metrics metrics;
  std::ostringstream s;
  for (size_t n = 0; n < metricsCount_; n++) {
    s << FORMANCC_BENCHMARK_METRICS_NAME_PREFIX << n;
    std::shared_ptr<Metric> m = std::shared_ptr<Metric>(new Metric());
    m->name = s.str();
    metrics.push_back(m);
  }

  memStore->setRetentionInterval(retentionIntervel_);
  memStore->setRetentionPeriod(FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC);

  for (std::shared_ptr<Metric> m : metrics) {
    memStore->addMetric(m);
  }

  if (!memStore->realloc())
    return false;

  return true;
}

////////////////////////////////////////////////
// insertRecords
////////////////////////////////////////////////

bool BenchmarkController::insertRecords(MemStore* memStore, size_t retensionPeriodHour, time_t& beginTs, time_t& endTs, size_t repeatCnt)
{
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC = (60 * 60 * retensionPeriodHour);
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_COUNT = (FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC / retentionIntervel_);

  beginTs = time(NULL);
  time_t metricTs = beginTs;
  for (size_t n = 0; n < FORMANCC_BENCHMARK_RETENSION_PERIOD_COUNT; n++) {
    Metrics values;
    for (size_t n = 0; n < repeatCnt; n++) {
      std::shared_ptr<std::vector<std::shared_ptr<Metric>>> metrics = memStore->getMetrics();
      for (auto it = metrics->begin(); it != metrics->end(); ++it) {
        std::shared_ptr<Metric> m = *it;
        std::shared_ptr<Metric> value = std::shared_ptr<Metric>(new Metric(*m));
        value->timestamp = metricTs;
        value->value = n;
        values.push_back(value);
      }
      if (!memStore->addValues(values))
        return false;
    }
    metricTs += retentionIntervel_;
  }
  endTs = metricTs;
  return true;
}

////////////////////////////////////////////////
// readRecords
////////////////////////////////////////////////

bool BenchmarkController::readRecords(MemStore* memStore, size_t retensionPeriodHour, time_t beginTs, time_t endTs, size_t repeatCnt)
{
  std::shared_ptr<std::vector<std::shared_ptr<Metric>>> metrics = memStore->getMetrics();
  for (size_t n = 0; n < repeatCnt; n++) {
    for (auto it = metrics->begin(); it != metrics->end(); ++it) {
      std::shared_ptr<Metric> m = *it;
      std::shared_ptr<MetricValue> values = nullptr;
      size_t valueCnt = 0;
      if (!memStore->getValues(*m, beginTs, endTs, retentionIntervel_, values, valueCnt))
        return false;
    }
  }
  return true;
}

////////////////////////////////////////////////
// finalize
////////////////////////////////////////////////

bool BenchmarkController::finalize(MemStore* memStore)
{
  memStore->close();
  return true;
}
