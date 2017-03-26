/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/MemStore.h>

using namespace Foreman;

////////////////////////////////////////////////
// TimeSeriesMapStore
////////////////////////////////////////////////

TimeSeriesMapStore::TimeSeriesMapStore()
{
  tsMap_ = std::shared_ptr<TimeSeriesMap>(new TimeSeriesMap());
}

TimeSeriesMapStore::~TimeSeriesMapStore()
{
}

////////////////////////////////////////////////
// addValue
////////////////////////////////////////////////

bool TimeSeriesMapStore::addValue(const Metric& m)
{
  return tsMap_->addValue(m);
}

////////////////////////////////////////////////
// getValues
////////////////////////////////////////////////

bool TimeSeriesMapStore::getValues(const Metric& m, time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt)
{
  return tsMap_->getValues(m, beginTs, endTs, interval, values, valueCnt);
}
