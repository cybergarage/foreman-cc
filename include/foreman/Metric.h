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

typedef std::pair<std::string, std::shared_ptr<Metric> > MetricsPair;

class MetricMap : public std::unordered_map<std::string, std::shared_ptr<Metric> > {
  public:
  MetricMap();
  virtual ~MetricMap();

  bool addMetric(std::shared_ptr<Metric> m);
  bool addMetrics(std::vector<std::shared_ptr<Metric> > metrics);
  std::shared_ptr<Metric> findMetric(const std::string& name);
};

class Metrics : public std::vector<std::shared_ptr<Metric> > {
  public:
  Metrics(){};
  virtual ~Metrics(){};
};
}

#endif
