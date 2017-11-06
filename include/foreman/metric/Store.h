/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
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
    virtual bool isOpened() = 0;
    virtual bool close() = 0;

    virtual bool setRetentionInterval(time_t value);
    virtual time_t getRetentionInterval();
    virtual bool setRetentionPeriod(time_t sec);
    virtual time_t getRetentionPeriod();

    virtual bool addMetric(std::shared_ptr<Metric> m);
    virtual std::shared_ptr<Metric> findMetric(const std::string& name);
    virtual std::shared_ptr<std::vector<std::shared_ptr<Metric>>> getMetrics();

    virtual bool addValue(const Metric& value) = 0;
    virtual bool addValues(const Metrics& values);

    virtual bool getValues(Query* q, ResultSet* rs) = 0;

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
