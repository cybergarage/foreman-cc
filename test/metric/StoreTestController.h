/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_STORETESTCONTROLLER_H_
#define _FOREMANCC_METRIC_STORETESTCONTROLLER_H_

#include <foreman/metric/impl/StoreImpl.h>

#define FORMANCC_STORETESTCONTROLLER_RETENSION_INTERVAL (60 * 5)
#define FORMANCC_STORETESTCONTROLLER_RETENSION_PERIOD_HOUR 6
#define FORMANCC_STORETESTCONTROLLER_RETENSION_PERIOD_SEC (60 * 60 * FORMANCC_STORETESTCONTROLLER_RETENSION_PERIOD_HOUR)

#define FORMANCC_STORETESTCONTROLLER_METRICS_COUNT 500
#define FORMANCC_STORETESTCONTROLLER_METRICS_NAME_PREFIX "name"

////////////////////////////////////////////////
// StoreTestContoller
////////////////////////////////////////////////

namespace Foreman {
namespace Metric {

  class StoreTestContollerConfig {
  public:
    StoreTestContollerConfig() {};
    
  public:
    time_t retentionInterval;
    time_t insertInterval;
    time_t retentionPeriod;
    size_t metricsCount;
    bool enableTimestampJitter;
  };
  
  class StoreTestContollerDefaultConfig : public StoreTestContollerConfig {
  public:
    StoreTestContollerDefaultConfig() {
      retentionInterval = FORMANCC_STORETESTCONTROLLER_RETENSION_INTERVAL;
      insertInterval = retentionInterval;
      retentionPeriod = FORMANCC_STORETESTCONTROLLER_RETENSION_PERIOD_SEC;
      metricsCount = FORMANCC_STORETESTCONTROLLER_METRICS_COUNT;
      enableTimestampJitter = false;
    };
  };
  
  class StoreTestContoller : public StoreTestContollerConfig {
public:
    StoreTestContoller(StoreTestContollerConfig config);
    virtual ~StoreTestContoller();

    void testAll(Foreman::Metric::Store* store);
    void testOnlyInsert(Foreman::Metric::Store* store);


  private:
    StoreTestContollerConfig config;
    
    time_t testMetricBeginTs;
    time_t testMetricEndTs;
    Foreman::Metric::MetricArray testMetrics;

    void initialize(Foreman::Metric::Store* store);
    void testInsertMetrics(Foreman::Metric::Store* store);
    void testQueryMetrics(Foreman::Metric::Store* store);
    void testInsertMetricsData(Foreman::Metric::Store* store);
    void testQueryMetricsData(Foreman::Metric::Store* store);
  };
}
}

#endif
