/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_STORE_H_
#define _FOREMANCC_STORE_H_

#include <foreman/Metric.h>
#include <foreman/Query.h>
#include <foreman/ResultSet.h>

namespace Foreman {

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

  virtual bool addMetric(const Metric& m);
  virtual std::shared_ptr<Metric> findMetric(const std::string& name);
  virtual std::shared_ptr<std::vector<std::shared_ptr<Metric>>> getMetrics();
  
  virtual bool addValue(const Metric& value) = 0;
  virtual bool addValues(const Metrics& values);

  virtual bool getValues(Query *q, ResultSet *rs) = 0;

protected:
  MetricMap metricMap_;
};
}

#endif
