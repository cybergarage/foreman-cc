/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <foreman/SQLiteStore.h>

using namespace Foreman;

BOOST_AUTO_TEST_CASE(NewSQLiteStore)
{
  MemStore *store = new SQLiteStore();
  delete store;
}
