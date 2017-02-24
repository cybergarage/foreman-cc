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
// ArrayTimeSeries
////////////////////////////////////////////////

ArrayTimeSeries::ArrayTimeSeries()
{
  values_ = nullptr;
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
  lastTs_ = m.timestamp;
  firstTs_ = lastTs_ - arraySize_;

  if (arrayCount_ < arraySize_)
    arrayCount_++;

  return true;
}

////////////////////////////////////////////////
// getValueCount
////////////////////////////////////////////////

bool ArrayTimeSeries::getValueCount(time_t beginTs, time_t endTs, time_t interval, size_t& valueCnt)
{
  if (endTs <= beginTs)
    return false;

  valueCnt = (endTs - beginTs) / interval;
  if (valueCnt <= 0)
    return false;

  if (arrayCount_ < valueCnt)
    valueCnt = arrayCount_;

  return true;
}

/////////////////////////////////////////////////
// reallocValueArray
////////////////////////////////////////////////

bool ArrayTimeSeries::reallocValueArray(size_t size)
{
  if (!clear())
    return false;

  values_ = new MetricValue[size];
  if (!values_)
    return false;

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

  values_ = values;
  arraySize_ = size;

  return true;
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool ArrayTimeSeries::clear()
{
  if (values_) {
    delete[] values_;
    values_ = nullptr;
  }

  arraySize_ = 0;
  arrayCount_ = 0;

  firstTs_ = 0;
  lastTs_ = 0;

  return true;
}
