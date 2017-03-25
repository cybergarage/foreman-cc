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
// BeringeiTimeSeries
////////////////////////////////////////////////

BeringeiTimeSeries::BeringeiTimeSeries()
{
}

BeringeiTimeSeries::~BeringeiTimeSeries() {}

////////////////////////////////////////////////
// addValue
////////////////////////////////////////////////

bool RingArrayTimeSeries::addValue(const Metric& m)
{
  return ArrayTimeSeries::addValue(m);
}

////////////////////////////////////////////////
// getValues
////////////////////////////////////////////////

bool RingArrayTimeSeries::getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt)
{
  return true;
}
