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
// TSmapStore
////////////////////////////////////////////////

TSmapStore::TSmapStore() {
}

TSmapStore::~TSmapStore() {
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool TSmapStore::open() {
  return true;
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool TSmapStore::isOpened() {
  return true;
}

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool TSmapStore::close() {
  return true;
}
