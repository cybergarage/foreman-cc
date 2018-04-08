/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_RESULTSET_H_
#define _FOREMANCC_METRIC_RESULTSET_H_

#include <foreman/Platform.h>
#include <foreman/metric/Metrics.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // ResultSet
  ////////////////////////////////////////////////

  class ResultSet {
public:
    ResultSet();
    virtual ~ResultSet();

    bool clear();

    bool addMetrics(Metrics* m)
    {
      return msArray_.addMetrics(m);
    }

    bool addMetrics(std::shared_ptr<Metrics> m)
    {
      return msArray_.addMetrics(m);
    }

    bool addMetrics(const std::string& name, time_t from, time_t interval, double* values, size_t valueCnt)
    {
      return msArray_.addMetrics(name, from, interval, values, valueCnt);
    }

    Metrics* findMetrics(const std::string& name)
    {
      return msArray_.findMetrics(name);
    }

    Metrics* firstMetrics();
    Metrics* nextMetrics();

    size_t getMetricsCount()
    {
      return msArray_.size();
    }

    bool addDataPoints(const std::string& name, time_t from, time_t interval, double* values, size_t valueCnt);

private:
    MetricsArray msArray_;
    MetricsArrayIt currIt_;
  };
}
}

#endif
