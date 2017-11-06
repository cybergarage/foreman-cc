/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/impl/TimeSeriesMapStore.h>

using namespace Foreman::Metric;

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

bool TimeSeriesMapStore::getValues(Query* q, ResultSet* rs)
{
  return tsMap_->getValues(q, rs);
}
