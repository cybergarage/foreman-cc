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

#include <foreman/MemStore.h>

using namespace Foreman;

////////////////////////////////////////////////
// ArrayTimeSeries
////////////////////////////////////////////////

ArrayTimeSeries::ArrayTimeSeries()
{
  clear();
}

ArrayTimeSeries::~ArrayTimeSeries()
{
  clear();
}

////////////////////////////////////////////////
// addMetric
////////////////////////////////////////////////

bool ArrayTimeSeries::addValue(const Metric& m)
{
  rawValues_[arrayInsertIndex_] = m.value;

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

bool ArrayTimeSeries::getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt)
{
  if (endTs <= beginTs)
    return false;

  valueCnt = (endTs - beginTs) / interval;
  if (valueCnt <= 0)
    return false;

  MetricValue* copyValues = new MetricValue[valueCnt];

  size_t arrayRightCnt = arraySize_ - arrayInsertIndex_;
  if (0 < arrayRightCnt) {
    memcpy(copyValues, (rawValues_ + arrayInsertIndex_), (sizeof(MetricValue) * arrayRightCnt));
  }

  size_t arrayLeftCnt = arrayInsertIndex_;
  if (0 < arrayLeftCnt) {
    memcpy((copyValues + arrayRightCnt), rawValues_, (sizeof(MetricValue) * arrayLeftCnt));
  }

  values = std::shared_ptr<MetricValue>(copyValues);

  return true;
}

////////////////////////////////////////////////
// reallocValueArray
////////////////////////////////////////////////

bool ArrayTimeSeries::reallocValueArray(size_t size)
{
  if (!clear())
    return false;

  rawValues_ = new MetricValue[size];
  if (!rawValues_)
    return false;

  values_ = std::shared_ptr<MetricValue>(rawValues_);
  arraySize_ = size;

  return true;
}

////////////////////////////////////////////////
// setValueArray
////////////////////////////////////////////////

bool ArrayTimeSeries::setValueArray(MetricValue* values, size_t size)
{
  if (!clear())
    return false;

  rawValues_ = values;
  arraySize_ = size;

  return true;
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool ArrayTimeSeries::clear()
{
  values_ = nullptr;
  rawValues_ = nullptr;

  arraySize_ = 0;
  arrayInsertIndex_ = 0;
  arrayCount_ = 0;

  firstTs_ = 0;
  lastTs_ = 0;

  return true;
}
