/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_STORE_H_
#define _FOREMANCC_METRIC_STORE_H_

#include <foreman/common/Error.h>
#include <foreman/metric/Metric.h>
#include <foreman/metric/Query.h>
#include <foreman/metric/ResultSet.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // Store
  ////////////////////////////////////////////////

  class Store {
public:
    Store();
    virtual ~Store() = 0;

    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual void clear() = 0;

    virtual bool setRetentionInterval(time_t value);
    virtual time_t getRetentionInterval();
    virtual bool setRetentionPeriod(time_t sec);
    virtual time_t getRetentionPeriod();

    virtual bool addMetric(std::shared_ptr<Metric> m) = 0;
    virtual bool queryMetric(Query* q, ResultSet* rs) = 0;

    virtual bool addData(const Metric& value) = 0;
    virtual bool addData(const MetricArray& values) = 0;

    virtual bool queryData(Query* q, ResultSet* rs) = 0;

    virtual bool analyzeData(Query* q, ResultSet* rs, Error* err);

    virtual size_t deleteExpiredMetrics() = 0;

protected:
    time_t retentionInterval_;
    time_t retentionPeriod_;
  };
}
}

#endif
