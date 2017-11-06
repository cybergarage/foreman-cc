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

#include <foreman/metric/impl/BeringeiStore.h>

using namespace Foreman::Metric;

#if defined(FOREMAN_ENABLE_BERINGEI)

////////////////////////////////////////////////
// BeringeiStore
////////////////////////////////////////////////

BeringeiStore::BeringeiStore()
{
  tsMap_ = std::shared_ptr<BeringeiTimeSeriesMap>(new BeringeiTimeSeriesMap());
}

BeringeiStore::~BeringeiStore() {}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool BeringeiStore::open() { return true; }

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool BeringeiStore::isOpened() { return true; }

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool BeringeiStore::close() { return true; }

#endif
