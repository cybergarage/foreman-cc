/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
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
// RingMapStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(RingMapStoreTest)
{
  StoreTestContoller testController;

  Store* store = new RingMapStore();
  testController.run(store);
  delete store;
}

////////////////////////////////////////////////
// NarrowTableStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(NarrowTableStoreTest)
{
  StoreTestContoller testController;

  Store* store = new NarrowTableStore();
  testController.run(store);
  delete store;
}

////////////////////////////////////////////////
// BeringeiStore
////////////////////////////////////////////////

#if defined(FOREMAN_ENABLE_BERINGEI)

BOOST_AUTO_TEST_CASE(BeringeiStoreTest)
{
  StoreTestContoller testController;

  Store* store = new BeringeiStore();
  testController.run(store);
  delete store;
}

#endif

BOOST_AUTO_TEST_SUITE_END()
