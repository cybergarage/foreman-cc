/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <algorithm>

#include <sqlite3.h>
#include <cstdio>

#include <foreman/metric/impl/ArrayTimeSeries.h>
#include <foreman/util/Util.h>

using namespace Foreman::Metric;

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
// getQueryDataCount
////////////////////////////////////////////////

bool ArrayTimeSeries::getQueryDataCount(Query* q, std::size_t* valueCnt)
{
  if (!q->getDataPointCount(valueCnt))
    return false;

  if (arrayCount_ < *valueCnt)
    *valueCnt = arrayCount_;

  return true;
}

/////////////////////////////////////////////////
// reallocValueArray
////////////////////////////////////////////////

bool ArrayTimeSeries::reallocValueArray(std::size_t size)
{
  if (!clear())
    return false;

  values_ = CreateNanDataPointValueArray(size);
  if (!values_)
    return false;

  arraySize_ = size;

  return true;
}

////////////////////////////////////////////////
// setValueArray
////////////////////////////////////////////////

bool ArrayTimeSeries::setValueArray(double* values, std::size_t size)
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
