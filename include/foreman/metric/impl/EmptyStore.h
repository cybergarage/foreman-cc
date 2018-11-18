/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_EMPTY_STORE_H_
#define _FOREMANCC_METRIC_EMPTY_STORE_H_

#include <foreman/Const.h>
#include <foreman/metric/Store.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // EmptyStore
  ////////////////////////////////////////////////

  class EmptyStore : public Store {
public:
    EmptyStore();
    ~EmptyStore();

    const char* getName() { return "empty"; }
    const char* getVersion() { return FOREMANCC_PRODUCT_VERSION; }

    bool open() { return true; }
    bool close() { return true; }
    bool clear() { return true; }

    bool setRetentionInterval(time_t value)
    {
      retentionInterval = value;
      return true;
    }
    time_t getRetentionInterval() { return retentionInterval; }
    bool setRetentionPeriod(time_t sec)
    {
      retentionPeriod = sec;
      return true;
    }
    time_t getRetentionPeriod() { return retentionPeriod; }

    bool addMetric(std::shared_ptr<Metric> m) { return true; }
    bool queryMetric(Query* q, ResultSet* rs) { return false; }

    bool addData(const Metric& value) { return true; }
    bool addData(const MetricArray& values) { return true; }

    bool queryData(Query* q, ResultSet* rs) { return false; }

    bool analyzeData(Query* q, ResultSet* rs, Error* err) { return false; }

    size_t deleteExpiredMetrics() { return 0; }

private:
    time_t retentionInterval;
    time_t retentionPeriod;
  };
}
}

#endif
