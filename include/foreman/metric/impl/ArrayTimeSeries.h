/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_ARRAY_TIMESERIES_H_
#define _FOREMANCC_METRIC_ARRAY_TIMESERIES_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <foreman/metric/impl/TimeSeries.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // ArrayTimeSeries
  ////////////////////////////////////////////////

  class ArrayTimeSeries : public TimeSeries {
public:
    ArrayTimeSeries();
    ~ArrayTimeSeries();

    virtual bool addValue(const Metric& m);
    virtual bool getValues(Query* q, ResultSet* rs) = 0;

    virtual bool reallocValueArray(size_t size);
    virtual bool setValueArray(double* values, size_t size);
    virtual bool clear();

protected:
    bool getQueryDataCount(Query* q, size_t* valueCnt);

    double* values_;

    size_t arraySize_;
    size_t arrayCount_;

    time_t firstTs_;
    time_t lastTs_;
  };

  class RingArrayTimeSeries : public ArrayTimeSeries {
public:
    RingArrayTimeSeries();
    ~RingArrayTimeSeries();

    bool addValue(const Metric& m);
    bool getValues(Query* q, ResultSet* rs);
    bool clear();

protected:
    size_t arrayInsertIndex_;
  };

  class StaticArrayTimeSeries : public ArrayTimeSeries {
public:
    StaticArrayTimeSeries();
    ~StaticArrayTimeSeries();

    bool addValue(const Metric& m);
    bool getValues(Query* q, ResultSet* rs);
  };
}
}

#endif
