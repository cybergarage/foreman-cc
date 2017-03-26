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

bool TimeSeries::getValueCount(time_t beginTs, time_t endTs, time_t interval, size_t& valueCnt)
{
  if (endTs <= beginTs)
    return false;
  
  valueCnt = ((endTs - beginTs) / interval) + 1;
  if (valueCnt <= 0)
    return false;
  
  return true;
}
