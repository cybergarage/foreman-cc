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

  MetricValue* rawValues = new MetricValue[rowCount * columnCount];
  if (rawValues == nullptr)
    return false;
  tsMap_->mxValues = std::shared_ptr<MetricValue>(rawValues);

  for (MetricsPair m : metricMap_) {
    std::shared_ptr<MatrixTimeSeries> ts = std::shared_ptr<MatrixTimeSeries>(new MatrixTimeSeries());
    if (!ts->setValueArray(rawValues, columnCount))
      return false;
    tsMap_->insert(std::make_pair(m.second->name, ts));
    rawValues += columnCount;
  }

  return true;
}
