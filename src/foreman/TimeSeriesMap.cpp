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
// find
////////////////////////////////////////////////

std::shared_ptr<TimeSeries> TimeSeriesMap::find(const Metric& m)
{
  TimeSeriesMap::const_iterator tsIt = std::unordered_map<std::string, std::shared_ptr<TimeSeries>>::find(m.name);
  if (tsIt == TimeSeriesMap::end())
    return nullptr;

  return tsIt->second;
}

////////////////////////////////////////////////
// addValue
////////////////////////////////////////////////

bool TimeSeriesMap::addValue(const Metric& m)
{
  std::shared_ptr<TimeSeries> ts = find(m);
  if (ts == nullptr)
    return false;

  return ts->addValue(m);
}

////////////////////////////////////////////////
// addValues
////////////////////////////////////////////////

bool TimeSeriesMap::addValues(std::vector<std::shared_ptr<Metric>> metrics)
{
  for (std::shared_ptr<Metric> m : metrics) {
    if (!addValue(*m))
      return false;
  }

  return true;
}

////////////////////////////////////////////////
// addValues
////////////////////////////////////////////////

bool TimeSeriesMap::getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& data)
{
  return false;
}
