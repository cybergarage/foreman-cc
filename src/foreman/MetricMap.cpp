/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
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
// addMetric
////////////////////////////////////////////////

bool MetricMap::addMetric(std::shared_ptr<Metric> m)
{
  insert(std::make_pair(m->name, m));
  return true;
}

////////////////////////////////////////////////
// findMetric
////////////////////////////////////////////////

std::shared_ptr<Metric> MetricMap::findMetric(const std::string& name)
{
  MetricMap::const_iterator tsIt = std::unordered_map<std::string, std::shared_ptr<Metric>>::find(name);
  if (tsIt == MetricMap::end())
    return nullptr;

  return tsIt->second;
}

////////////////////////////////////////////////
// findMetric
////////////////////////////////////////////////

std::shared_ptr<std::vector<std::shared_ptr<Metric>>> MetricMap::getMetrics()
{
  std::shared_ptr<Metrics> mm = std::shared_ptr<Metrics>(new Metrics());
  for (auto it = begin(); it != end(); ++it) {
    mm->addMetric(*it->second);
  }
  return mm;
}

////////////////////////////////////////////////
// addMetrics
////////////////////////////////////////////////

bool MetricMap::addMetrics(std::vector<std::shared_ptr<Metric>> metrics)
{
  for (std::shared_ptr<Metric> m : metrics) {
    if (!addMetric(m))
      return false;
  }

  return true;
}
