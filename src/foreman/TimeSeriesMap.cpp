/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/TimeSeries.h>

using namespace Foreman;

////////////////////////////////////////////////
// TimeSeriesMap
////////////////////////////////////////////////

TimeSeriesMap::TimeSeriesMap()
{
}

TimeSeriesMap::~TimeSeriesMap()
{
}

////////////////////////////////////////////////
// addMetric
////////////////////////////////////////////////

bool TimeSeriesMap::addValue(const Metric &m)
{
  TimeSeriesMap::const_iterator tsIt = find(m.name);
  if (tsIt == TimeSeriesMap::end())
    return false;
  
  std::shared_ptr<TimeSeries> ts = tsIt->second;
  return ts->addValue(m);
}

////////////////////////////////////////////////
// addMetrics
////////////////////////////////////////////////

bool TimeSeriesMap::addValues(std::vector<std::shared_ptr<Metric>> metrics)
{
  for (std::shared_ptr<Metric> m : metrics) {
    if (!addValue(*m))
      return false;
  }
  
  return true;
}
