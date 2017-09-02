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
#include <foreman/Util.h>

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
  double* newValues = CreateNanDataPointValueArray(arraySize_);
  if (!newValues)
    return false;

  if (!ArrayTimeSeries::addValue(m))
    return false;

  memcpy(newValues, (values_ + 1), (sizeof(double) * (arraySize_ - 1)));
  delete values_;

  values_ = newValues;
  values_[(arraySize_ - 1)] = m.value;

  return true;
}

////////////////////////////////////////////////
// getMetricsValues
////////////////////////////////////////////////

bool StaticArrayTimeSeries::getValues(Query* q, ResultSet* rs)
{
  size_t valueCount;
  if (!getQueryDataCount(q, &valueCount))
    return false;

  return rs->addDataPoints(q->getTarget(), q->getFrom(), q->getInterval(), values_, valueCount);
}
