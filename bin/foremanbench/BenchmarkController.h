/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_BENCHMARKCONTROLLER_H_
#define _FOREMANCC_BENCHMARKCONTROLLER_H_

#include <foreman/Foreman.h>

namespace Foreman {

#define FORMANCC_BENCHMARK_DEFAULT_RETENSION_INTERVAL 60
#define FORMANCC_BENCHMARK_DEFAULT_METRICS_COUNT 1000
#define FORMANCC_BENCHMARK_METRICS_NAME_PREFIX "name"

////////////////////////////////////////////////
// BenchmarkController
////////////////////////////////////////////////

typedef enum _BenchmarkControllerRecordType : int {
  BenchmarkControllerRandomRecordType,
  BenchmarkControllerPeriodicRecordType,
  BenchmarkControllerSporadicRecordType,
  BenchmarkControllerConstantRecordType,
} BenchmarkControllerRecordType;

class BenchmarkController {
  public:
  BenchmarkController();
  virtual ~BenchmarkController();

  void setRetentionIntervel(time_t value) { retentionIntervel_ = value; }
  void setMetricsCount(size_t value) { metricsCount_ = value; }

  bool initialize(MemStore* memStore, size_t retensionPeriodHour);
  bool insertRecords(MemStore* memStore, size_t retensionPeriodHour, time_t& beginTs, time_t& endTs, BenchmarkControllerRecordType recordType, size_t repeatCnt = 1);
  bool readRecords(MemStore* memStore, size_t retensionPeriodHour, time_t beginTs, time_t endTs, size_t repeatCnt = 1);
  bool finalize(MemStore* memStore);

  private:
  time_t retentionIntervel_;
  size_t metricsCount_;
};
}

#endif
