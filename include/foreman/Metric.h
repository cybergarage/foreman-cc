/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_H_
#define _FOREMANCC_METRIC_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <time.h>

#include <foreman/Platform.h>

namespace Foreman {

////////////////////////////////////////////////
// Metric
////////////////////////////////////////////////

typedef double MetricValue;

class Metric {
  public:
  Metric();
  virtual ~Metric();

  std::string name;
  MetricValue value;
  time_t timestamp;
};

////////////////////////////////////////////////
// Metrics
////////////////////////////////////////////////

typedef std::pair<std::string, std::shared_ptr<Metric>> MetricsPair;

class MetricMap : public std::unordered_map<std::string, std::shared_ptr<Metric>> {
  public:
  MetricMap();
  virtual ~MetricMap();

  bool addMetric(const Metric &m);
  bool addMetrics(std::vector<std::shared_ptr<Metric>> metrics);
  std::shared_ptr<Metric> findMetric(const std::string& name);
  std::shared_ptr<std::vector<std::shared_ptr<Metric>>> getMetrics();
};

class Metrics : public std::vector<std::shared_ptr<Metric>> {
  public:
  Metrics(){};
  virtual ~Metrics(){};
  bool addMetric(const Metric &m)
  {
    std::shared_ptr<Foreman::Metric> cm = std::shared_ptr<Foreman::Metric>(new Foreman::Metric(m));
    push_back(cm);
    return true;
  }
};
}

#endif
