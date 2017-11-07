/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_QUERY_H_
#define _FOREMANCC_METRIC_QUERY_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <time.h>

#include <foreman/Platform.h>
#include <foreman/metric/Metric.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // Query
  ////////////////////////////////////////////////

  class Query {
public:
    Query();
    virtual ~Query();

    bool setTarget(const std::string& value)
    {
      target = value;
      return true;
    }

    bool setTarget(const Metric& m)
    {
      target = m.name.c_str();
      return true;
    }

    const char* getTarget()
    {
      return target.c_str();
    }

    bool setFrom(time_t value)
    {
      from = value;
      return true;
    }

    time_t getFrom()
    {
      return from;
    }

    bool setUntil(time_t value)
    {
      until = value;
      return true;
    }

    time_t getUntil()
    {
      return until;
    }

    bool setInterval(time_t value)
    {
      interval = value;
      return true;
    }

    time_t getInterval()
    {
      return interval;
    }

    bool getDataPointCount(size_t* count);

public:
    std::string target;
    time_t from;
    time_t until;
    time_t interval;
  };
}
}

#endif
