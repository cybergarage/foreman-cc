/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <sqlite3.h>
#include <stdio.h>

#include <foreman/metric/impl/RingMapStore.h>
#include <foreman/util/Util.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// RingMapStore
////////////////////////////////////////////////

RingMapStore::RingMapStore()
{
}

RingMapStore::~RingMapStore()
{
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool RingMapStore::open() { return true; }

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool RingMapStore::isOpened() { return true; }

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool RingMapStore::close() { return true; }

////////////////////////////////////////////////
// realloc
////////////////////////////////////////////////

bool RingMapStore::realloc()
{
  size_t columnCount = getColumnCount();

  if (columnCount <= 0)
    return false;

  tsMap_->clear();

  for (MetricsPair m : metricMap_) {
    double* rowData = CreateNanDataPointValueArray(columnCount);
    if (rowData == nullptr)
      return false;
    std::shared_ptr<RingMapTimeSeries> ts = std::shared_ptr<RingMapTimeSeries>(new RingMapTimeSeries());
    if (!ts->reallocValueArray(columnCount))
      return false;
    tsMap_->insert(std::make_pair(m.second->name, ts));
  }

  return true;
}
