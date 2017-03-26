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

#include <foreman/MemStore.h>

using namespace Foreman;

////////////////////////////////////////////////
// TSmapStore
////////////////////////////////////////////////

TSmapStore::TSmapStore()
{
  tsMap_ = std::shared_ptr<TSmapTimeSeriesMap>(new TSmapTimeSeriesMap());
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
