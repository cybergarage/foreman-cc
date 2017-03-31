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

#include "MemStoreTestController.h"

using namespace Foreman;

////////////////////////////////////////////////
// MatrixStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(MatrixStoreTest)
{
  MemStoreTestContoller testController;

  MemStore* store = new MatrixStore();
  testController.run(store);
  delete store;
}

////////////////////////////////////////////////
// RingMapStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(RingMapStoreTest)
{
  MemStoreTestContoller testController;

  MemStore* store = new RingMapStore();
  testController.run(store);
  delete store;
}

////////////////////////////////////////////////
// NarrowTableStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(NarrowTableStoreTest)
{
  MemStoreTestContoller testController;

  MemStore* store = new NarrowTableStore();
  testController.run(store);
  delete store;
}

////////////////////////////////////////////////
// TSmapStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(TSmapStoreTest)
{
  MemStoreTestContoller testController;

  MemStore* store = new TSmapStore();
  testController.run(store);
  delete store;
}
