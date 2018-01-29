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
#include <foreman/register/impl/MemStore.h>

BOOST_AUTO_TEST_SUITE(register_)

using namespace Foreman::Register;

////////////////////////////////////////////////
// MemStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(MemStore)
{
  StoreTestContoller testController;

  MemStore* store = new MemStore();
  //testController.run(store);
  delete store;
}

BOOST_AUTO_TEST_SUITE_END()
