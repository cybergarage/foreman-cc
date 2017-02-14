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
// WideTableStore
////////////////////////////////////////////////

WideTableStore::WideTableStore() {
}

WideTableStore::~WideTableStore() {
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool WideTableStore::open() {
  if (!SQLiteStore::open())
    return false;
  return true;
}
