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

bool MemStore::addMetric(std::shared_ptr<Metric> m)
{
  return metricMap_.addMetric(m);
}

////////////////////////////////////////////////
// findMetric
////////////////////////////////////////////////

std::shared_ptr<Metric> MemStore::findMetric(const std::string& name)
{
  return metricMap_.findMetric(name);
}

////////////////////////////////////////////////
// findMetric
////////////////////////////////////////////////

std::shared_ptr<std::vector<std::shared_ptr<Metric>>> MemStore::getMetrics()
{
  return metricMap_.getMetrics();
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
