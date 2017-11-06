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

#include <foreman/metric/impl/BeringeiTimeSeries.h>
#include <foreman/metric/impl/MemStore.h>

using namespace Foreman::Metric;

#if defined(FOREMAN_ENABLE_BERINGEI)

////////////////////////////////////////////////
// TSmapStore
////////////////////////////////////////////////

TSmapStore::TSmapStore()
{
  tsMap_ = std::shared_ptr<BeringeiTimeSeriesMap>(new BeringeiTimeSeriesMap());
}

TSmapStore::~TSmapStore() {}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool TSmapStore::open() { return true; }

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool TSmapStore::isOpened() { return true; }

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool TSmapStore::close() { return true; }

#endif
