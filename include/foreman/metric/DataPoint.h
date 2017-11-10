/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_DATAPOINT_H_
#define _FOREMANCC_METRIC_DATAPOINT_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <time.h>

#include <foreman/Platform.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // DataPoint
  ////////////////////////////////////////////////

  class DataPoint {
public:
    DataPoint();
    virtual ~DataPoint();

    void setValue(double value)
    {
      value_ = value;
    }

    double getValue()
    {
      return value_;
    }

    void setTimestamp(double value)
    {
      timestamp_ = value;
    }

    double getTimestamp()
    {
      return timestamp_;
    }

private:
    double value_;
    time_t timestamp_;
  };

  ////////////////////////////////////////////////
  // DataPoints
  ////////////////////////////////////////////////

  class DataPoints : public std::vector<std::shared_ptr<DataPoint>> {
public:
    DataPoints();
    virtual ~DataPoints();

    void setName(const std::string& name)
    {
      name_ = name;
    }

    const char* getName()
    {
      return name_.c_str();
    }

    bool addDataPoint(DataPoint* dp);
    bool addDataPoint(const DataPoint& dp);
    bool addDataPoint(std::shared_ptr<Foreman::Metric::DataPoint> dp);
    bool addDataPoints(time_t from, time_t interval, double* values, size_t valueCnt);

    DataPoint* getDataPoint(size_t n);

protected:
    std::string name_;
  };

  ////////////////////////////////////////////////
  // DataPointMap
  ////////////////////////////////////////////////

  typedef std::pair<std::string, std::shared_ptr<DataPoints>> DataPointsPair;
  typedef std::unordered_map<std::string, std::shared_ptr<DataPoints>>::iterator DataPointsMapIt;

  class DataPointsMap : public std::unordered_map<std::string, std::shared_ptr<DataPoints>> {
public:
    DataPointsMap();
    virtual ~DataPointsMap();

    bool addDataPoints(DataPoints* dps);
    bool addDataPoints(std::shared_ptr<DataPoints> dps);
    bool addDataPoints(const std::string& name, time_t from, time_t interval, double* values, size_t valueCnt);

    DataPoints* findDataPoints(const std::string& name);
  };
}
}

#endif
