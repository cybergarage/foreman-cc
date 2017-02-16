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
// MemStore
////////////////////////////////////////////////

MemStore::MemStore()
{
  retentionInterval_ = 0;
  retentionPeriod_ = 0;
}

MemStore::~MemStore() {}

////////////////////////////////////////////////
// addMetric
////////////////////////////////////////////////

bool MemStore::addMetric(const Metric& metric)
{
  metrics_.push_back(std::unique_ptr<Metric>(new Metric(metric)));
  return true;
}
