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
#include <uhttp/net/Socket.h>

using namespace Foreman;

////////////////////////////////////////////////
// GraphiteStore
////////////////////////////////////////////////

GraphiteStore::GraphiteStore(const char *host, int carbonPort, int httpPort)
{
  host_ = host;
  carbonPort_ = carbonPort;
  httpPort_ = httpPort;
}

GraphiteStore::~GraphiteStore()
{
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool GraphiteStore::open() { return true; }

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool GraphiteStore::isOpened() { return true; }

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool GraphiteStore::close() { return true; }

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
