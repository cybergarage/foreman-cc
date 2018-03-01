/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/Metrics.h>
#include <foreman/util/Util.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// DataPoints
////////////////////////////////////////////////

Metrics::Metrics()
{
}

Metrics::~Metrics() {}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool Metrics::addDataPoint(DataPoint* dp)
{
  return addDataPoint(std::shared_ptr<Foreman::Metric::DataPoint>(dp));
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool Metrics::addDataPoint(const DataPoint& dp)
{
  return addDataPoint(new Foreman::Metric::DataPoint(dp));
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool Metrics::addDataPoint(std::shared_ptr<Foreman::Metric::DataPoint> dp)
{
  push_back(dp);
  return true;
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool Metrics::addDataPoints(time_t from, time_t interval, double* values, size_t valueCnt)
{
  time_t ts = from;
  for (int n = 0; n < valueCnt; n++) {
    if (!IsValidDataPointValue(values[n])) {
      ts += interval;
      continue;
    }

    DataPoint* dp = new DataPoint();
    if (!dp)
      return false;

    dp->setTimestamp(ts);
    dp->setValue(values[n]);

    if (!addDataPoint(std::shared_ptr<Foreman::Metric::DataPoint>(dp)))
      return false;

    ts += interval;
  }

  return true;
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

DataPoint* Metrics::getDataPoint(size_t n)
{
  if ((size() - 1) < n)
    return NULL;
  return at(n).get();
}

////////////////////////////////////////////////
// getMaxValueIndex
////////////////////////////////////////////////

ssize_t Metrics::getMaxValueIndex()
{
  double lastMaxValue = NAN;
  size_t lastMaxValueIndex = -1;
  size_t n = 0;
  for (auto dp : *this) {
    if (n == 0) {
      lastMaxValueIndex = 0;
      lastMaxValue = dp->getValue();
    }
    else if (lastMaxValue <= dp->getValue()) {
      lastMaxValueIndex = n;
      lastMaxValue = dp->getValue();
    }
    n++;
  }

  return lastMaxValueIndex;
}

////////////////////////////////////////////////
// getMetricsValues (ALGLIB)
////////////////////////////////////////////////

#if defined(FOREMAN_ENABLE_ALGLIB)

bool Metrics::getMetricsValues(alglib::real_1d_array& realArray)
{
  auto metricsCount = size();
  realArray.setlength(metricsCount);
  for (size_t n = 0; n < metricsCount; n++) {
    auto dp = getDataPoint(n);
    realArray[n] = dp->getValue();
  }

  return true;
}

#endif
