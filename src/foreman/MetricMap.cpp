/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Metric.h>

using namespace Foreman;

////////////////////////////////////////////////
// MetricMap
////////////////////////////////////////////////

MetricMap::MetricMap()
{
}

MetricMap::~MetricMap()
{
}

////////////////////////////////////////////////
// findMetric
////////////////////////////////////////////////

std::shared_ptr<Metric> MetricMap::findMetric(const std::string& name)
{
  MetricMap::const_iterator tsIt = std::unordered_map<std::string, std::shared_ptr<Metric> >::find(name);
  if (tsIt == MetricMap::end())
    return nullptr;

  return tsIt->second;
}

////////////////////////////////////////////////
// addMetric
////////////////////////////////////////////////

bool MetricMap::addMetric(std::shared_ptr<Metric> m)
{
  insert(MetricsPair{ m->name, m });
  return true;
}

////////////////////////////////////////////////
// addMetrics
////////////////////////////////////////////////

bool MetricMap::addMetrics(std::vector<std::shared_ptr<Metric> > metrics)
{
  for (std::shared_ptr<Metric> m : metrics) {
    if (!addMetric(m))
      return false;
  }

  return true;
}
