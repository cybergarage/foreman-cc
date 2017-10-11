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

#include <foreman/MemStore.h>
#include <foreman/TimeSeriesMap.h>

using namespace Foreman;

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
