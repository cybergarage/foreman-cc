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
  values_[arrayInsertIndex_] = m.value;

  lastTs_ = m.timestamp;
  firstTs_ = lastTs_ - arraySize_;

  arrayInsertIndex_++;
  if (arraySize_ <= arrayInsertIndex_)
    arrayInsertIndex_ = 0;

  if (arrayCount_ < arraySize_)
    arrayCount_++;

  return true;
}

////////////////////////////////////////////////
// getMetricsValues
////////////////////////////////////////////////

bool StaticArrayTimeSeries::getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt)
{
  if (endTs <= beginTs)
    return false;

  valueCnt = (endTs - beginTs) / interval;
  if (valueCnt <= 0)
    return false;

  MetricValue* copyValues = new MetricValue[valueCnt];

  size_t arrayRightCnt = arraySize_ - arrayInsertIndex_;
  if (0 < arrayRightCnt) {
    memcpy(copyValues, (values_ + arrayInsertIndex_), (sizeof(MetricValue) * arrayRightCnt));
  }

  size_t arrayLeftCnt = arrayInsertIndex_;
  if (0 < arrayLeftCnt) {
    memcpy((copyValues + arrayRightCnt), values_, (sizeof(MetricValue) * arrayLeftCnt));
  }

  values = std::shared_ptr<MetricValue>(copyValues);

  return true;
}
