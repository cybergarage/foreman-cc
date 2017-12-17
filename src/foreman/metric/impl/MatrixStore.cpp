/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <sqlite3.h>

#include <foreman/metric/impl/MatrixStore.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// MatrixStore
////////////////////////////////////////////////

MatrixStore::MatrixStore()
{
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

  for (MetricsPair m : metricMap_) {
    std::shared_ptr<MatrixTimeSeries> ts = std::shared_ptr<MatrixTimeSeries>(new MatrixTimeSeries());
    if (!ts->reallocValueArray(columnCount))
      return false;
    tsMap_->insert(std::make_pair(m.second->name, ts));
  }

  return true;
}
