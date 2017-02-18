/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <iostream>

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

bool ArrayTimeSeries::addMetric(Metric& data)
{
  return true;
}

////////////////////////////////////////////////
// getMetricsValues
////////////////////////////////////////////////

bool ArrayTimeSeries::getMetricsValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& data)
{
  ssize_t valueCnt = (endTs - beginTs) / interval;
  if (valueCnt <= 0)
    return false;

  MetricValue* copyData = new MetricValue[valueCnt];
  data = std::shared_ptr<MetricValue>(copyData);
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

  return true;
}
