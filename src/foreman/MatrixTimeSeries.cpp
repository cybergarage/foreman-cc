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
// MatrixTimeSeries
////////////////////////////////////////////////

MatrixTimeSeries::MatrixTimeSeries()
{
  row = nullptr;
  rowSize = 0;
}

MatrixTimeSeries::~MatrixTimeSeries()
{
}

////////////////////////////////////////////////
// getData
////////////////////////////////////////////////

bool MatrixTimeSeries::getData(size_t offset, size_t length, std::shared_ptr<MetricData>& data)
{
  MetricData* copyData = new MetricData[length];
  data = std::shared_ptr<MetricData>(copyData);
  return true;
}

////////////////////////////////////////////////
// getDataSize
////////////////////////////////////////////////

size_t MatrixTimeSeries::getDataSize()
{
  return rowSize;
}
