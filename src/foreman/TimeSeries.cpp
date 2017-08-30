/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/TimeSeries.h>

using namespace Foreman;

////////////////////////////////////////////////
// TimeSeries
////////////////////////////////////////////////

TimeSeries::TimeSeries()
{
}

TimeSeries::~TimeSeries() {}

////////////////////////////////////////////////
// getValueCount
////////////////////////////////////////////////

bool TimeSeries::getValueCount(Query* q, size_t* valueCnt)
{
  if (q->until <= q->from)
    return false;

  *valueCnt = ((q->until - q->from) / q->interval);
  if (*valueCnt <= 0)
    return false;

  return true;
}
