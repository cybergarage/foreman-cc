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
  if (!getValueCount(beginTs, endTs, interval, valueCnt))
    return false;

  std::string data;
  stream_.readData(data);

  std::vector<TimeValuePair> out;
  facebook::gorilla::TimeSeriesStream::readValues(out, data, (int)valueCnt, beginTs, endTs);
  
  MetricValue* copyValues = new MetricValue[valueCnt];
  for(auto v : out) {
    if ((v.unixTime < beginTs) || (endTs < v.unixTime))
      continue;
    int idx = (int)((v.unixTime - beginTs) / interval);
    if ((idx < 0) || ((valueCnt-1) < idx))
      continue;
    copyValues[idx] = v.value;
  }
  values = std::shared_ptr<MetricValue>(copyValues);

  return true;
}
