/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_TIMESERIES_H_
#define _FOREMANCC_TIMESERIES_H_

#include <beringei/TimeSeriesStream.h>
#include <foreman/Metric.h>

namespace Foreman {

////////////////////////////////////////////////
// TimeSeries
////////////////////////////////////////////////

class TimeSeries {
  public:
  TimeSeries();
  virtual ~TimeSeries();

  virtual bool addValue(const Metric& m) = 0;
  virtual bool getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt) = 0;
};

////////////////////////////////////////////////
// ArrayTimeSeries
////////////////////////////////////////////////

class ArrayTimeSeries : public TimeSeries {
  public:
  ArrayTimeSeries();
  ~ArrayTimeSeries();

  virtual bool addValue(const Metric& m);
  virtual bool getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& data, size_t& valueCnt) = 0;

  virtual bool reallocValueArray(size_t size);
  virtual bool setValueArray(MetricValue* values, size_t size);
  virtual bool clear();

  protected:
  bool getValueCount(time_t beginTs, time_t endTs, time_t interval, size_t& valueCnt);

  MetricValue* values_;

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
  bool getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& data, size_t& valueCnt);
  bool clear();

  protected:
  size_t arrayInsertIndex_;
};

class StaticArrayTimeSeries : public ArrayTimeSeries {
  public:
  StaticArrayTimeSeries();
  ~StaticArrayTimeSeries();

  bool addValue(const Metric& m);
  bool getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& data, size_t& valueCnt);
};

////////////////////////////////////////////////
// BeringeiTimeSeries
////////////////////////////////////////////////

class BeringeiTimeSeries : public TimeSeries {
  public:
  BeringeiTimeSeries();
  ~BeringeiTimeSeries();

  bool addValue(const Metric& m);
  bool getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt);

  private:
  facebook::gorilla::TimeSeriesStream stream_;
};
}

#endif
