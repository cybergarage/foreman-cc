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

bool TimeSeriesMapStore::getValues(Query* q, ResultSet* rs)
{
  return tsMap_->getValues(q, rs);
}
