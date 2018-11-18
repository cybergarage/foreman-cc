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

#define FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL 60
#define FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_HOUR 6
#define FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_SEC (60 * 60 * FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_HOUR)
#define FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT (FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_SEC / FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL)

#define FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT 500
#define FORMANCC_MEMSTORETESTCONTROLLER_METRICS_NAME_PREFIX "name"

////////////////////////////////////////////////
// StoreTestContoller
////////////////////////////////////////////////

namespace Foreman {
namespace Metric {

  class StoreTestContoller {
public:
    StoreTestContoller();
    virtual ~StoreTestContoller();

    void runAllTests(Foreman::Metric::Store* store);
    void runOnlyInsertTests(Foreman::Metric::Store* store);

private:
    time_t testMetricBeginTs;
    time_t testMetricEndTs;
    Foreman::Metric::MetricArray testMetrics;

    void runInitializeTest(Foreman::Metric::Store* store);
    void runInsertMetricsTest(Foreman::Metric::Store* store);
    void runQueryMetricsTest(Foreman::Metric::Store* store);
    void runInsertMetricsDataTest(Foreman::Metric::Store* store);
    void runQueryMetricsDataTest(Foreman::Metric::Store* store);
  };
}
}

#endif
