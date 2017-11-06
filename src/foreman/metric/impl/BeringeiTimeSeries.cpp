/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/impl/BeringeiTimeSeries.h>
#include <foreman/util/Util.h>

using namespace Foreman::Metric;

#if defined(FOREMAN_ENABLE_BERINGEI)

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

bool BeringeiTimeSeries::getValues(Query* q, ResultSet* rs)
{
  size_t valueCount;
  if (!q->getDataPointCount(&valueCount))
    return false;

  double* values = CreateNanDataPointValueArray(valueCount);
  if (!values)
    return false;

  std::string data;
  stream_.readData(data);

  std::vector<TimeValuePair> out;
  facebook::gorilla::TimeSeriesStream::readValues(out, data, (int)valueCount, q->from, q->until);

  for (auto v : out) {
    if ((v.unixTime < q->from) || (q->until < v.unixTime))
      continue;
    int idx = (int)((v.unixTime - q->from) / q->interval);
    if ((idx < 0) || ((valueCount - 1) < idx))
      continue;
    values[idx] = v.value;
  }

  bool isSuccess = rs->addDataPoints(q->getTarget(), q->getFrom(), q->getInterval(), values, valueCount);

  delete values;

  return isSuccess;
}

#endif
