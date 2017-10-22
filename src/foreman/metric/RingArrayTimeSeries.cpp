/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <algorithm>

#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

#include <foreman/metric/MemStore.h>
#include <foreman/util/Util.h>

using namespace Foreman::Metric;

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

bool RingArrayTimeSeries::getValues(Query* q, ResultSet* rs)
{
  size_t valueCount;
  if (!getQueryDataCount(q, &valueCount))
    return false;

  double* values = CreateNanDataPointValueArray(valueCount);
  if (!values)
    return false;

  size_t arrayRightCnt = arraySize_ - arrayInsertIndex_;
  if (0 < arrayRightCnt) {
    memcpy(values, (values_ + arrayInsertIndex_), (sizeof(double) * arrayRightCnt));
  }

  size_t arrayLeftCnt = arrayInsertIndex_;
  if (0 < arrayLeftCnt) {
    memcpy((values + arrayRightCnt), values_, (sizeof(double) * arrayLeftCnt));
  }

  bool isSuccess = rs->addDataPoints(q->getTarget(), q->getFrom(), q->getInterval(), values, valueCount);

  delete[] values;

  return isSuccess;
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool RingArrayTimeSeries::clear()
{
  arrayInsertIndex_ = 0;
  return ArrayTimeSeries::clear();
}
