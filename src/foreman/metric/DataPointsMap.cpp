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

using namespace Foreman::Metric;

////////////////////////////////////////////////
// DataPointsMap
////////////////////////////////////////////////

DataPointsMap::DataPointsMap()
{
}

DataPointsMap::~DataPointsMap()
{
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool DataPointsMap::addDataPoints(DataPoints* dps)
{
  return addDataPoints(std::shared_ptr<DataPoints>(dps));
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool DataPointsMap::addDataPoints(std::shared_ptr<DataPoints> dps)
{
  insert(std::make_pair(dps->getName(), dps));
  return true;
}

////////////////////////////////////////////////
// addDataPoints
////////////////////////////////////////////////

bool DataPointsMap::addDataPoints(const std::string& name, time_t from, time_t interval, double* values, size_t valueCnt)
{
  DataPoints* dps = findDataPoints(name);
  if (!dps) {
    dps = new Foreman::Metric::DataPoints();
    if (!dps)
      return false;
    dps->setName(name);
    if (!addDataPoints(dps))
      return false;
  }

  return dps->addDataPoints(from, interval, values, valueCnt);
}

////////////////////////////////////////////////
// findDataPoints
////////////////////////////////////////////////

DataPoints* DataPointsMap::findDataPoints(const std::string& name)
{
  DataPointsMap::const_iterator dpIt = std::unordered_map<std::string, std::shared_ptr<DataPoints>>::find(name);
  if (dpIt == DataPointsMap::end())
    return nullptr;

  return dpIt->second.get();
}
