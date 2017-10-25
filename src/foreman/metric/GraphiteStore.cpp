/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <sqlite3.h>
#include <stdio.h>

#include <foreman/Const.h>
#include <foreman/metric/MemStore.h>

using namespace Foreman::Metric;

#if defined(FOREMAN_ENABLE_GRAPHITE)

////////////////////////////////////////////////
// GraphiteStore
////////////////////////////////////////////////

GraphiteStore::GraphiteStore()
{
}

GraphiteStore::~GraphiteStore()
{
}

////////////////////////////////////////////////
// setHost
////////////////////////////////////////////////

void GraphiteStore::setHost(const std::string& host)
{
  graphite.setHost(host);
}

////////////////////////////////////////////////
// setCarbonPort
////////////////////////////////////////////////

void GraphiteStore::setCarbonPort(int port)
{
  graphite.setCarbonPort(port);
}

////////////////////////////////////////////////
// setHttpPort
////////////////////////////////////////////////

void GraphiteStore::setHttpPort(int port)
{
  graphite.setHttpPort(port);
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool GraphiteStore::open()
{
  return true;
}

////////////////////////////////////////////////
// isOpened
////////////////////////////////////////////////

bool GraphiteStore::isOpened()
{
  return true;
}

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool GraphiteStore::close()
{
  return true;
}

////////////////////////////////////////////////
// addValue
////////////////////////////////////////////////

bool GraphiteStore::addValue(const Metric& m)
{
  return graphite.addValue(m.name, m.timestamp, m.value);
}

////////////////////////////////////////////////
// getValues
////////////////////////////////////////////////

bool GraphiteStore::getValues(Query* q, ResultSet* rs)
{
  if (!q || !rs)
    return false;

  double* values = NULL;
  size_t valueCout = 0;

  if (!graphite.getValues(q->target, q->from, q->until, q->interval, &values, &valueCout))
    return false;

  bool isSuccess = rs->addDataPoints(q->getTarget(), q->getFrom(), q->getInterval(), values, valueCout);

  if (values) {
    delete[] values;
  }

  return isSuccess;
}

#endif
