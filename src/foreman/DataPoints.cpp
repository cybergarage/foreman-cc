/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/DataPoint.h>
#include <foreman/Util.h>

using namespace Foreman;

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
  return addDataPoint(std::shared_ptr<Foreman::DataPoint>(dp));
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool DataPoints::addDataPoint(const DataPoint& dp)
{
  return addDataPoint(new Foreman::DataPoint(dp));
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool DataPoints::addDataPoint(std::shared_ptr<Foreman::DataPoint> dp)
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

    if (!addDataPoint(std::shared_ptr<Foreman::DataPoint>(dp)))
      return false;

    ts += interval;
  }

  return true;
}
