/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <boost/test/unit_test.hpp>

#include "StoreTestController.h"

using namespace Foreman::Metric;

BOOST_AUTO_TEST_SUITE(metric)

////////////////////////////////////////////////
// MatrixStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(MatrixStoreTest)
{
  StoreTestContoller testController;

  MemStore* store = new MatrixStore();
  testController.run(store);
  delete store;
}

////////////////////////////////////////////////
// RingMapStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(RingMapStoreTest)
{
  StoreTestContoller testController;

  MemStore* store = new RingMapStore();
  testController.run(store);
  delete store;
}

////////////////////////////////////////////////
// NarrowTableStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(NarrowTableStoreTest)
{
  StoreTestContoller testController;

  MemStore* store = new NarrowTableStore();
  testController.run(store);
  delete store;
}

////////////////////////////////////////////////
// TSmapStore
////////////////////////////////////////////////

#if defined(FOREMAN_ENABLE_BERINGEI)

BOOST_AUTO_TEST_CASE(TSmapStoreTest)
{
  StoreTestContoller testController;

  MemStore* store = new TSmapStore();
  //testController.run(store);
  delete store;
}

#endif

BOOST_AUTO_TEST_SUITE_END()
