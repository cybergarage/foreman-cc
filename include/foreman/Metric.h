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

#include <string>
#include <vector>
#include <memory>

#include <time.h>

#include <foreman/Platform.h>

namespace Foreman {

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

  typedef std::vector<std::unique_ptr<Metric>> Metrics;
}

#endif
