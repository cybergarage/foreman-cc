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
// TSmapStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(TSmapStoreTest)
{
  MemStoreTestContoller testController;

  MemStore* store = new TSmapStore();
  //testController.run(store);
  delete store;
}

////////////////////////////////////////////////
// WideTableStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(WideTableStoreTest)
{
  MemStoreTestContoller testController;

  MemStore* store = new WideTableStore();
  //testController.run(store);
  delete store;
}

////////////////////////////////////////////////
// MatrixStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(MatrixStoreTest)
{
  MemStoreTestContoller testController;

  MemStore* store = new MatrixStore();
  //testController.run(store);
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
