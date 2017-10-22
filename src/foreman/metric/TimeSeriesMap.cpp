/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/TimeSeriesMap.h>

using namespace Foreman::Metric;

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
// findTimeSeries
////////////////////////////////////////////////

std::shared_ptr<TimeSeries> TimeSeriesMap::findTimeSeries(const Metric& m)
{
  TimeSeriesMap::const_iterator tsIt = std::unordered_map<std::string, std::shared_ptr<TimeSeries>>::find(m.name);
  if (tsIt == TimeSeriesMap::end())
    return nullptr;

  return tsIt->second;
}

////////////////////////////////////////////////
// createTimeSeries
////////////////////////////////////////////////

std::shared_ptr<TimeSeries> TimeSeriesMap::createTimeSeries(const Metric& m)
{
  return nullptr;
}

////////////////////////////////////////////////
// addTimeSeries
////////////////////////////////////////////////

std::shared_ptr<TimeSeries> TimeSeriesMap::addTimeSeries(const Metric& m)
{
  std::shared_ptr<TimeSeries> ts = createTimeSeries(m);
  if (ts == nullptr)
    return nullptr;
  insert(std::make_pair(m.name, ts));
  return ts;
}

////////////////////////////////////////////////
// addValue
////////////////////////////////////////////////

bool TimeSeriesMap::addValue(const Metric& m)
{
  std::shared_ptr<TimeSeries> ts = findTimeSeries(m);
  if (ts == nullptr) {
    ts = createTimeSeries(m);
    if (ts == nullptr)
      return false;
    insert(std::make_pair(m.name, ts));
  }

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
// getValues
////////////////////////////////////////////////

bool TimeSeriesMap::getValues(Query* q, ResultSet* rs)
{
  Metric m;
  m.name = q->target;

  std::shared_ptr<TimeSeries> ts = findTimeSeries(m);
  if (ts == nullptr)
    return false;

  return ts->getValues(q, rs);
}
