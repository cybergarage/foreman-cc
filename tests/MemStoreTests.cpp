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

#include <foreman/MemStore.h>

using namespace Foreman;

BOOST_AUTO_TEST_CASE(NewMemStore)
{
  MemStore *store = new MemStore();
  delete store;
}