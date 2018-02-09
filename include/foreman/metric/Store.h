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
    virtual ~Store();

    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual bool clear() = 0;

    virtual bool setRetentionInterval(time_t value);
    virtual time_t getRetentionInterval();
    virtual bool setRetentionPeriod(time_t sec);
    virtual time_t getRetentionPeriod();

    virtual bool addMetric(std::shared_ptr<Metric> m);
    virtual std::shared_ptr<Metric> findMetric(const std::string& name);
    virtual std::shared_ptr<MetricArray> getAllMetric();

    virtual bool getData(const Metric& value) = 0;
    virtual bool getData(const MetricArray& values);

    virtual bool queryData(Query* q, ResultSet* rs) = 0;

    virtual size_t getMemoryUsage() = 0;
    virtual size_t getStorageUsage() = 0;

protected:
    MetricMap metricMap_;
    time_t retentionInterval_;
    time_t retentionPeriod_;
  };
}
}

#endif
