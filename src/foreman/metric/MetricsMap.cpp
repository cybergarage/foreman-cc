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
// MetricsMap
////////////////////////////////////////////////

MetricsMap::MetricsMap()
{
}

MetricsMap::~MetricsMap()
{
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool MetricsMap::addMetrics(Metrics* dps)
{
  return addMetrics(std::shared_ptr<Metrics>(dps));
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool MetricsMap::addMetrics(std::shared_ptr<Metrics> dps)
{
  insert(std::make_pair(dps->getName(), dps));
  return true;
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool MetricsMap::addMetrics(const std::string& name, time_t from, time_t interval, double* values, size_t valueCnt)
{
  Metrics* dps = findMetrics(name);
  if (!dps) {
    dps = new Foreman::Metric::Metrics();
    if (!dps)
      return false;
    dps->setName(name);
    if (!addMetrics(dps))
      return false;
  }

  return dps->addDataPoints(from, interval, values, valueCnt);
}

////////////////////////////////////////////////
// findDataPoints
////////////////////////////////////////////////

Metrics* MetricsMap::findMetrics(const std::string& name)
{
  MetricsMap::const_iterator dpIt = std::unordered_map<std::string, std::shared_ptr<Metrics>>::find(name);
  if (dpIt == MetricsMap::end())
    return nullptr;

  return dpIt->second.get();
}
