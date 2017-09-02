/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/DataPoint.h>

using namespace Foreman;

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

bool DataPointsMap::addDataPoints(const std::string& name, std::shared_ptr<DataPoints> dps)
{
  insert(std::make_pair(name, dps));
  return true;
}

////////////////////////////////////////////////
// findDataPoints
////////////////////////////////////////////////

std::shared_ptr<DataPoints> DataPointsMap::findDataPoints(const std::string& name)
{
  DataPointsMap::const_iterator tsIt = std::unordered_map<std::string, std::shared_ptr<DataPoints>>::find(name);
  if (tsIt == DataPointsMap::end())
    return nullptr;

  return tsIt->second;
}
