/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <math.h>

#include <foreman/MemStore.h>

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
// addMetric
////////////////////////////////////////////////

bool MemStore::addMetric(const Metric& m)
{
  metrics_.push_back(std::unique_ptr<Metric>(new Metric(m)));
  return true;
}

////////////////////////////////////////////////
// addValues
////////////////////////////////////////////////

bool MemStore::addValues(const Metrics& values)
{
  for (std::shared_ptr<Foreman::Metric> value : values) {
    if (!addValue(*value))
      return false;
  }

  return true;
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
  return metrics_.size();
}
