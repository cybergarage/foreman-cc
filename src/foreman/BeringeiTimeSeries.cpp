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

bool BeringeiTimeSeries::addValue(const Metric& m)
{
  if (!stream_.append(m.timestamp, m.value, 0))
    return false;
  return true;
}

////////////////////////////////////////////////
// getValues
////////////////////////////////////////////////

bool BeringeiTimeSeries::getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt)
{
  return true;
}
