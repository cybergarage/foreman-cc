/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/Metrics.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// MetricsArray
////////////////////////////////////////////////

MetricsArray::MetricsArray()
{
}

MetricsArray::~MetricsArray()
{
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool MetricsArray::addMetrics(Metrics* ms)
{
  return addMetrics(std::shared_ptr<Metrics>(ms));
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool MetricsArray::addMetrics(std::shared_ptr<Metrics> ms)
{
  push_back(ms);
  return true;
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool MetricsArray::addMetrics(const std::string& name, time_t from, time_t interval, double* values, size_t valueCnt)
{
  Metrics* ms = findMetrics(name);
  if (!ms) {
    ms = new Foreman::Metric::Metrics();
    if (!ms)
      return false;
    ms->setName(name);
    if (!addMetrics(ms))
      return false;
  }

  return ms->addDataPoints(from, interval, values, valueCnt);
}

////////////////////////////////////////////////
// findDataPoints
////////////////////////////////////////////////

Metrics* MetricsArray::findMetrics(const std::string& name)
{
  for (auto msIt = begin(); msIt != end(); msIt++) {
    if (name.compare((*msIt)->getName()) == 0)
      return (*msIt).get();
  }
  return NULL;
}
