/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_RESULTSET_H_
#define _FOREMANCC_RESULTSET_H_

#include <foreman/DataPoint.h>
#include <foreman/Platform.h>

namespace Foreman {

////////////////////////////////////////////////
// ResultSet
////////////////////////////////////////////////

class ResultSet {
  public:
  ResultSet();
  virtual ~ResultSet();

  bool clear();

  bool addDataPoints(std::shared_ptr<DataPoints> dps)
  {
    return dataPointsMap_.addDataPoints(dps);
  }

  std::shared_ptr<DataPoints> findDataPoints(const std::string& name)
  {
    return dataPointsMap_.findDataPoints(name);
  }

  std::shared_ptr<DataPoints> gets();
  std::shared_ptr<DataPoints> next();

  private:
  DataPointsMap dataPointsMap_;
  DataPointsMap::const_iterator currIt_;
};
}

#endif
