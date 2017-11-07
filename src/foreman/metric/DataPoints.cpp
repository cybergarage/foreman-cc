/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/DataPoint.h>
#include <foreman/util/Util.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// DataPoints
////////////////////////////////////////////////

DataPoints::DataPoints()
{
}

DataPoints::~DataPoints() {}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool DataPoints::addDataPoint(DataPoint* dp)
{
  return addDataPoint(std::shared_ptr<Foreman::Metric::DataPoint>(dp));
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool DataPoints::addDataPoint(const DataPoint& dp)
{
  return addDataPoint(new Foreman::Metric::DataPoint(dp));
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool DataPoints::addDataPoint(std::shared_ptr<Foreman::Metric::DataPoint> dp)
{
  push_back(dp);
  return true;
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool DataPoints::addDataPoints(time_t from, time_t interval, double* values, size_t valueCnt)
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
