/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdio.h>
#include <sqlite3.h>

#include <foreman/MemStore.h>

using namespace Foreman;

////////////////////////////////////////////////
// RingMapStore
////////////////////////////////////////////////

RingMapStore::RingMapStore() {
}

RingMapStore::~RingMapStore() {
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool RingMapStore::open() {
  return true;
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool RingMapStore::isOpened() {
  return true;
}

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool RingMapStore::close() {
  return true;
}
