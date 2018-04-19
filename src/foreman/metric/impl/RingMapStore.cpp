/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <ctime>
#include <iostream>
#include <sqlite3.h>
#include <stdio.h>

#include <foreman/metric/impl/RingMapStore.h>
#include <foreman/util/Util.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// RingMapStore
////////////////////////////////////////////////

RingMapStore::RingMapStore()
{
}

RingMapStore::~RingMapStore()
{
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool RingMapStore::open() { return true; }

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool RingMapStore::isOpened() { return true; }

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool RingMapStore::close() { return true; }

////////////////////////////////////////////////
// deleteExpiredMetrics
////////////////////////////////////////////////

size_t RingMapStore::deleteExpiredMetrics()
{
  // TODO
  return 0;
}
