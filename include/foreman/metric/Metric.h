/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_METRIC_H_
#define _FOREMANCC_METRIC_METRIC_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <time.h>

#include <foreman/Platform.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // Metric
  ////////////////////////////////////////////////

  class Metric {
public:
    Metric();
    virtual ~Metric();

    std::string name;
    double value;
    time_t timestamp;
  };

  ////////////////////////////////////////////////
  // Metrics
  ////////////////////////////////////////////////

  typedef std::pair<std::string, std::shared_ptr<Metric>> MetricPair;

  class MetricMap : public std::unordered_map<std::string, std::shared_ptr<Metric>> {
public:
    MetricMap();
    virtual ~MetricMap();

    bool addMetric(std::shared_ptr<Metric> m);
    bool addMetrics(std::vector<std::shared_ptr<Metric>> metrics);
    std::shared_ptr<Metric> findMetric(const std::string& name);
    std::shared_ptr<std::vector<std::shared_ptr<Metric>>> getMetrics();
  };

  class MetricArray : public std::vector<std::shared_ptr<Metric>> {
public:
    MetricArray(){};
    virtual ~MetricArray(){};
    bool addMetric(const Metric& m)
    {
      auto cm = std::shared_ptr<Foreman::Metric::Metric>(new Foreman::Metric::Metric(m));
      push_back(cm);
      return true;
    }
  };
}
}

#endif
