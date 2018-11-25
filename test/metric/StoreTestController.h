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

#include "StoreTestConfig.h"
#include <foreman/metric/impl/StoreImpl.h>

////////////////////////////////////////////////
// StoreTestContoller
////////////////////////////////////////////////

namespace Foreman {
namespace Metric {

  class StoreTestContoller : public StoreTestConfig {
public:
    StoreTestContoller(StoreTestConfig config);
    virtual ~StoreTestContoller();

    void testAll(Foreman::Metric::Store* store);
    void testOnlyInsert(Foreman::Metric::Store* store);

private:
    StoreTestConfig config;

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
