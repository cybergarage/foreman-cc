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

bool MetricsMap::addMetrics(Metrics* ms)
{
  return addMetrics(std::shared_ptr<Metrics>(ms));
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool MetricsMap::addMetrics(std::shared_ptr<Metrics> ms)
{
  insert(std::make_pair(ms->getName(), ms));
  return true;
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool MetricsMap::addMetrics(const std::string& name, time_t from, time_t interval, double* values, size_t valueCnt)
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

Metrics* MetricsMap::findMetrics(const std::string& name)
{
  auto dpIt = std::unordered_map<std::string, std::shared_ptr<Metrics>>::find(name);
  if (dpIt == MetricsMap::end())
    return nullptr;

  return dpIt->second.get();
}
