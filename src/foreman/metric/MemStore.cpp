/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <math.h>

#include <foreman/metric/MemStore.h>

using namespace Foreman;

////////////////////////////////////////////////
// MemStore
////////////////////////////////////////////////

MemStore::MemStore()
{
  retentionInterval_ = 0;
  retentionPeriod_ = 0;
}

MemStore::~MemStore()
{
}

////////////////////////////////////////////////
// getColumnCount
////////////////////////////////////////////////

size_t MemStore::getColumnCount()
{
  if (retentionInterval_ == 0)
    return 0;
  return (int)(ceil(((double)retentionPeriod_ / (double)retentionInterval_)));
}

////////////////////////////////////////////////
// getRowCount
////////////////////////////////////////////////

size_t MemStore::getRowCount()
{
  return metricMap_.size();
}
