/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_METRICS_H_
#define _FOREMANCC_METRIC_METRICS_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <time.h>

#include <foreman/Platform.h>
#include <foreman/metric/DataPoint.h>

#if defined(FOREMAN_ENABLE_ALGLIB)
#include <alglib/ap.h>
#endif

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // Metrics
  ////////////////////////////////////////////////

  class Metrics : public std::vector<std::shared_ptr<DataPoint>> {
public:
    Metrics();
    virtual ~Metrics();

    void setName(const std::string& name)
    {
      name_ = name;
    }

    const char* getName()
    {
      return name_.c_str();
    }

    bool addDataPoint(DataPoint* dp);
    bool addDataPoint(const DataPoint& dp);
    bool addDataPoint(std::shared_ptr<DataPoint> dp);
    bool addDataPoints(time_t from, time_t interval, double* values, size_t valueCnt);

    DataPoint* getDataPoint(size_t n);

#if defined(FOREMAN_ENABLE_ALGLIB)
    bool getMetricsValues(alglib::real_1d_array &array);
#endif
    
protected:
    std::string name_;
  };

  ////////////////////////////////////////////////
  // MetricsMap
  ////////////////////////////////////////////////

  typedef std::pair<std::string, std::shared_ptr<Metrics>> MetricsPair;
  typedef std::unordered_map<std::string, std::shared_ptr<Metrics>>::iterator DataPointsMapIt;

  class MetricsMap : public std::unordered_map<std::string, std::shared_ptr<Metrics>> {
public:
    MetricsMap();
    virtual ~MetricsMap();

    bool addMetrics(Metrics* dps);
    bool addMetrics(std::shared_ptr<Metrics> dps);
    bool addMetrics(const std::string& name, time_t from, time_t interval, double* values, size_t valueCnt);

    Metrics* findMetrics(const std::string& name);
  };
}
}

#endif
