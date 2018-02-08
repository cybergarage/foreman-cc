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

    bool addDataPoints(Metrics* dps)
    {
      return dataPointsMap_.addMetrics(dps);
    }

    bool addDataPoints(std::shared_ptr<Metrics> dps)
    {
      return dataPointsMap_.addMetrics(dps);
    }

    bool addDataPoints(const std::string& name, time_t from, time_t interval, double* values, size_t valueCnt)
    {
      return dataPointsMap_.addMetrics(name, from, interval, values, valueCnt);
    }

    Metrics* findDataPoints(const std::string& name)
    {
      return dataPointsMap_.findMetrics(name);
    }

    Metrics* firstDataPoint();
    Metrics* nextDataPoint();

    size_t getDataPointCount()
    {
      return dataPointsMap_.size();
    }

private:
    MetricsMap dataPointsMap_;
    DataPointsMapIt currIt_;
  };
}
}

#endif
