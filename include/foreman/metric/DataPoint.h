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

    bool isValid() {
      if (isinf(value_) || isnan(value_)) {
        return false;
      }
      return true;
    }

private:
    double value_;
    time_t timestamp_;
  };
}
}

#endif
