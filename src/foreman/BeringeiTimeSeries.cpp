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

bool BeringeiTimeSeries::getValues(Query *q, ResultSet *rs)
{
  if (!getValueCount(q, &rs->valueCount))
    return false;

  std::string data;
  stream_.readData(data);

  std::vector<TimeValuePair> out;
  facebook::gorilla::TimeSeriesStream::readValues(out, data, (int)rs->valueCount, q->from, q->until);

  rs->values = new double[rs->valueCount];
  for (auto v : out) {
    if ((v.unixTime < q->from) || (q->until < v.unixTime))
      continue;
    int idx = (int)((v.unixTime - q->from) / q->interval);
    if ((idx < 0) || ((rs->valueCount - 1) < idx))
      continue;
    rs->values[idx] = v.value;
  }

  return true;
}
