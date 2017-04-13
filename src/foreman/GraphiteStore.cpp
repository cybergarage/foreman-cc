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

#include <foreman/Const.h>
#include <foreman/MemStore.h>

using namespace Foreman;

////////////////////////////////////////////////
// GraphiteStore
////////////////////////////////////////////////

GraphiteStore::GraphiteStore() {}

GraphiteStore::~GraphiteStore() {}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool GraphiteStore::open()
{
  return true;
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool GraphiteStore::clear()
{
  return true;
}

////////////////////////////////////////////////
// addValue
////////////////////////////////////////////////

bool GraphiteStore::addValue(const Metric& m)
{
  return true;
}

////////////////////////////////////////////////
// getValues
////////////////////////////////////////////////

bool GraphiteStore::getValues(const Metric& m, time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt)
{
  return true;
}
