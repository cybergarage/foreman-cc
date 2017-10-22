/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_RESULTSET_H_
#define _FOREMANCC_RESULTSET_H_

#include <foreman/Platform.h>
#include <foreman/metric/DataPoint.h>

namespace Foreman {

////////////////////////////////////////////////
// ResultSet
////////////////////////////////////////////////

class ResultSet {
  public:
  ResultSet();
  virtual ~ResultSet();

  bool clear();

  bool addDataPoints(DataPoints* dps)
  {
    return dataPointsMap_.addDataPoints(dps);
  }

  bool addDataPoints(std::shared_ptr<DataPoints> dps)
  {
    return dataPointsMap_.addDataPoints(dps);
  }

  bool addDataPoints(const std::string& name, time_t from, time_t interval, double* values, size_t valueCnt)
  {
    return dataPointsMap_.addDataPoints(name, from, interval, values, valueCnt);
  }

  DataPoints* findDataPoints(const std::string& name)
  {
    return dataPointsMap_.findDataPoints(name);
  }

  DataPoints* firstDataPoint();
  DataPoints* nextDataPoint();

  size_t getDataPointCount()
  {
    return dataPointsMap_.size();
  }

  private:
  DataPointsMap dataPointsMap_;
  DataPointsMapIt currIt_;
};
}

#endif
