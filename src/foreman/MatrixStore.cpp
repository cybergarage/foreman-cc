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
// MatrixStore
////////////////////////////////////////////////

MatrixStore::MatrixStore() {
}

MatrixStore::~MatrixStore() {
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool MatrixStore::open() {
  return true;
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool MatrixStore::isOpened() {
  return true;
}

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool MatrixStore::close() {
  return true;
}
