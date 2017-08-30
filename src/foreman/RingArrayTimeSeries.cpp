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

bool RingArrayTimeSeries::getValues(Query* q, ResultSet* rs)
{
  if (!getValueCount(q, &rs->valueCount))
    return false;

  rs->values = new double[rs->valueCount];

  size_t arrayRightCnt = arraySize_ - arrayInsertIndex_;
  if (0 < arrayRightCnt) {
    memcpy(rs->values, (values_ + arrayInsertIndex_), (sizeof(double) * arrayRightCnt));
  }

  size_t arrayLeftCnt = arrayInsertIndex_;
  if (0 < arrayLeftCnt) {
    memcpy((rs->values + arrayRightCnt), values_, (sizeof(double) * arrayLeftCnt));
  }

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
