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
#include <random>
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

bool BenchmarkController::insertRecords(MemStore* memStore, size_t retensionPeriodHour, time_t& beginTs, time_t& endTs, BenchmarkControllerRecordType recordType, size_t repeatCnt)
{
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC = (60 * 60 * retensionPeriodHour);
  size_t FORMANCC_BENCHMARK_RETENSION_PERIOD_COUNT = (FORMANCC_BENCHMARK_RETENSION_PERIOD_SEC / retentionIntervel_);

  double FORMANCC_BENCHMARK_RECORD_MIN = 1.0;
  double FORMANCC_BENCHMARK_RECORD_MAX = (double)FORMANCC_BENCHMARK_RETENSION_PERIOD_COUNT / 10.0;

  double FORMANCC_BENCHMARK_RECORD_CONSTANT_VAL = FORMANCC_BENCHMARK_RECORD_MIN;
  
  double FORMANCC_BENCHMARK_RECORD_PERIODIC_MIN = FORMANCC_BENCHMARK_RECORD_MIN;
  double FORMANCC_BENCHMARK_RECORD_PERIODIC_MAX = FORMANCC_BENCHMARK_RECORD_MAX;
  double FORMANCC_BENCHMARK_RECORD_PERIODIC_STEP = 1.0;

  double FORMANCC_BENCHMARK_RECORD_SPORADIC_NORMAL = FORMANCC_BENCHMARK_RECORD_MIN;
  double FORMANCC_BENCHMARK_RECORD_SPORADIC_THRESHOLD = FORMANCC_BENCHMARK_RECORD_MAX * 0.9;

  std::random_device rndDev;
  std::mt19937 mt(rndDev());
  std::uniform_int_distribution<> randDist(0, (int)FORMANCC_BENCHMARK_RETENSION_PERIOD_COUNT);

  double recordValue = 0.0;
  switch (recordType) {
    case BenchmarkControllerPeriodicRecordType:
      recordValue = FORMANCC_BENCHMARK_RECORD_PERIODIC_MIN;
      break;
    case BenchmarkControllerConstantRecordType:
      recordValue = FORMANCC_BENCHMARK_RECORD_CONSTANT_VAL;
      break;
    default:
      break;
  }
  
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
        
        switch (recordType) {
          case BenchmarkControllerRandomRecordType:
            recordValue = randDist(mt);
            break;
          case BenchmarkControllerPeriodicRecordType:
            recordValue += FORMANCC_BENCHMARK_RECORD_PERIODIC_STEP;
            if (recordValue < FORMANCC_BENCHMARK_RECORD_PERIODIC_MIN || FORMANCC_BENCHMARK_RECORD_PERIODIC_MAX < recordValue)
              FORMANCC_BENCHMARK_RECORD_PERIODIC_STEP *= -1.0;
            break;
          case BenchmarkControllerSporadicRecordType:
            recordValue = (FORMANCC_BENCHMARK_RECORD_SPORADIC_THRESHOLD < randDist(mt)) ? randDist(mt) : FORMANCC_BENCHMARK_RECORD_SPORADIC_NORMAL;
            break;
          default:
            break;
        }
        value->value = recordValue;
        
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
