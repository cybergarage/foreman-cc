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
// RingArrayTimeSeries
////////////////////////////////////////////////

RingArrayTimeSeries::RingArrayTimeSeries()
{
}

RingArrayTimeSeries::~RingArrayTimeSeries()
{
}

////////////////////////////////////////////////
// addMetric
////////////////////////////////////////////////

bool RingArrayTimeSeries::addValue(const Metric& m)
{
  values_[arrayInsertIndex_] = m.value;
  
  arrayInsertIndex_++;
  if (arraySize_ <= arrayInsertIndex_)
    arrayInsertIndex_ = 0;

  return ArrayTimeSeries::addValue(m);
}

////////////////////////////////////////////////
// getMetricsValues
////////////////////////////////////////////////

bool RingArrayTimeSeries::getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt)
{
  if (!getValueCount(beginTs, endTs, interval, valueCnt))
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

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool RingArrayTimeSeries::clear()
{
  arrayInsertIndex_ = 0;
  return ArrayTimeSeries::clear();
}

