/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include "StoreTestController.h"
#include <foreman/registry/impl/StoreImpl.h>

using namespace Foreman::Registry;

BOOST_AUTO_TEST_SUITE(registry)

////////////////////////////////////////////////
// SQLite
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(SQLiteStore)
{
  StoreTestContoller testController;

  SQLiteStore* store = new SQLiteStore();
  //testController.run(store);
  delete store;
}

BOOST_AUTO_TEST_SUITE_END()
