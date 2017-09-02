/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_DATAPOINT_H_
#define _FOREMANCC_DATAPOINT_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <time.h>

#include <foreman/Platform.h>

namespace Foreman {

////////////////////////////////////////////////
// DataPoint
////////////////////////////////////////////////

class DataPoint {
  public:
  DataPoint();
  virtual ~DataPoint();

  double value;
  time_t timestamp;
};

////////////////////////////////////////////////
// DataPoints
////////////////////////////////////////////////

class DataPoints : public std::vector<std::shared_ptr<DataPoint>> {
  public:
  DataPoints(){};
  virtual ~DataPoints(){};

  bool addDataPoint(const DataPoint& m)
  {
    std::shared_ptr<Foreman::DataPoint> cm = std::shared_ptr<Foreman::DataPoint>(new Foreman::DataPoint(m));
    push_back(cm);
    return true;
  }

  std::string name;
};

////////////////////////////////////////////////
// DataPointMap
////////////////////////////////////////////////

typedef std::pair<std::string, std::shared_ptr<DataPoints>> DataPointsPair;

class DataPointsMap : public std::unordered_map<std::string, std::shared_ptr<DataPoints>> {
  public:
  DataPointsMap();
  virtual ~DataPointsMap();

  bool addDataPoints(std::shared_ptr<DataPoints> dps);
  std::shared_ptr<DataPoints> findDataPoints(const std::string& name);
};
}

#endif
