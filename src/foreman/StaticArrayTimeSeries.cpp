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
  double* newValues = new double[arraySize_];
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
  if (!getValueCount(q, &rs->count))
    return false;

  rs->values = new double[rs->count];
  memcpy(rs->values, values_, (sizeof(double) * rs->count));

  return true;
}
