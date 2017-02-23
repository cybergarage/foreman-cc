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

template <typename MetricsType>
class MetricsTemplate : public std::vector<std::shared_ptr<MetricsType>> {
public:
  MetricsTemplate(){};
  virtual ~MetricsTemplate(){};
};

class Metrics : public MetricsTemplate<Metric> {
public:
  Metrics(){};
  virtual ~Metrics(){};
};

}

#endif
