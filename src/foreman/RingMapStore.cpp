/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <sqlite3.h>
#include <stdio.h>

#include <foreman/MemStore.h>

using namespace Foreman;

////////////////////////////////////////////////
// RingMapStore
////////////////////////////////////////////////

RingMapStore::RingMapStore()
{
  tsMap_ = std::shared_ptr<RingMapTimeSeriesMap>(new RingMapTimeSeriesMap());
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
  
  for (std::shared_ptr<Metric> m : metrics_) {
    MetricData* rowData = new MetricData[columnCount];
    if (rowData == nullptr)
      return false;
    std::shared_ptr<MatrixTimeSeries> ts = std::shared_ptr<MatrixTimeSeries>(new MatrixTimeSeries());
    ts->row = rowData;
    ts->rowSize = columnCount;
    tsMap_->insert(TimeSeriesPair{ m->name, ts });
  }
  
  return true;
}
