/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/Metric.h>

using namespace Foreman::Metric;

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
  auto tsIt = std::unordered_map<std::string, std::shared_ptr<Metric>>::find(name);
  if (tsIt == MetricMap::end())
    return nullptr;

  return tsIt->second;
}

////////////////////////////////////////////////
// findMetric
////////////////////////////////////////////////

std::shared_ptr<std::vector<std::shared_ptr<Metric>>> MetricMap::getMetrics()
{
  auto mm = std::shared_ptr<MetricArray>(new MetricArray());
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
  for (auto m : metrics) {
    if (!addMetric(m))
      return false;
  }

  return true;
}
