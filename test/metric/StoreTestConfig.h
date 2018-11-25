/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_TEST_CONST_H_
#define _FOREMANCC_METRIC_TEST_CONST_H_

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

  class StoreTestConfig {
public:
    StoreTestConfig() {};

public:
    time_t retentionInterval;
    time_t insertInterval;
    time_t retentionPeriod;
    size_t metricsCount;
    bool enableTimestampJitter;
  };

  class DefaultStoreTestConfig : public StoreTestConfig {
public:
    DefaultStoreTestConfig()
    {
      retentionInterval = FORMANCC_STORETESTCONTROLLER_RETENSION_INTERVAL;
      insertInterval = retentionInterval;
      retentionPeriod = FORMANCC_STORETESTCONTROLLER_RETENSION_PERIOD_SEC;
      metricsCount = FORMANCC_STORETESTCONTROLLER_METRICS_COUNT;
      enableTimestampJitter = false;
    };
  };
}
}

#endif
