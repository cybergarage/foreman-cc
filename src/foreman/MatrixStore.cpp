/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <iostream>

#include <sqlite3.h>
#include <stdio.h>

#include <foreman/MemStore.h>

using namespace Foreman;

////////////////////////////////////////////////
// MatrixStore
////////////////////////////////////////////////

MatrixStore::MatrixStore()
{
  tsMap_ = std::shared_ptr<MatrixTimeSeriesMap>(new MatrixTimeSeriesMap());
}

MatrixStore::~MatrixStore()
{
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool MatrixStore::open() { return true; }

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool MatrixStore::isOpened() { return true; }

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool MatrixStore::close() { return true; }

////////////////////////////////////////////////
// realloc
////////////////////////////////////////////////

bool MatrixStore::realloc()
{
  size_t rowCount = getRowCount();
  size_t columnCount = getColumnCount();

  if (rowCount <= 0 || columnCount <= 0)
    return false;

  tsMap_->clear();

  MetricData* rowData = new MetricData[rowCount * columnCount];
  if (rowData == nullptr)
    return false;
  tsMap_->data = std::shared_ptr<MetricData>(rowData);

  for (std::shared_ptr<Metric> m : metrics_) {
    std::shared_ptr<MatrixTimeSeries> ts = std::shared_ptr<MatrixTimeSeries>(new MatrixTimeSeries());
    ts->row = rowData;
    tsMap_->insert(TimeSeriesPair{ m->name, ts });
    rowData += columnCount;
  }

  return true;
}
