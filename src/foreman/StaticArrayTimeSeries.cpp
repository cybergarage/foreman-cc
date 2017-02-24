/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <algorithm>

#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

#include <foreman/MemStore.h>

using namespace Foreman;

////////////////////////////////////////////////
// StaticArrayTimeSeries
////////////////////////////////////////////////

StaticArrayTimeSeries::StaticArrayTimeSeries()
{
}

StaticArrayTimeSeries::~StaticArrayTimeSeries()
{
}

////////////////////////////////////////////////
// addMetric
////////////////////////////////////////////////

bool StaticArrayTimeSeries::addValue(const Metric& m)
{
  MetricValue* newValues = new MetricValue[arraySize_];
  if (!newValues)
    return false;

  if (!ArrayTimeSeries::addValue(m))
    return false;

  memcpy(newValues, (values_ + 1), (sizeof(MetricValue) * (arraySize_ - 1)));
  delete values_;

  values_ = newValues;
  values_[(arraySize_ - 1)] = m.value;

  return true;
}

////////////////////////////////////////////////
// getMetricsValues
////////////////////////////////////////////////

bool StaticArrayTimeSeries::getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt)
{
  if (!getValueCount(beginTs, endTs, interval, valueCnt))
    return false;

  MetricValue* copyValues = new MetricValue[valueCnt];
  memcpy(copyValues, values_, (sizeof(MetricValue) * valueCnt));
  values = std::shared_ptr<MetricValue>(copyValues);

  return true;
}
