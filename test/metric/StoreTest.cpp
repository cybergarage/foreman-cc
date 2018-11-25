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
// NarrowTableStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(NarrowTableStoreTest)
{
  DefaultStoreTestContollerConfig config;
  StoreTestContoller testController(config);

  Store* store = new NarrowTableStore();
  testController.testAll(store);
  delete store;
}

BOOST_AUTO_TEST_CASE(NarrowTableStoreMassiveTest)
{
  DefaultStoreTestContollerConfig config;
  config.retentionInterval = 60 * 5;
  config.insertInterval = 60;
  StoreTestContoller testController(config);
  
  Store* store = new NarrowTableStore();
  testController.testAll(store);
  delete store;
}

BOOST_AUTO_TEST_CASE(NarrowTableStoreMassiveWithJitterTest)
{
  DefaultStoreTestContollerConfig config;
  config.retentionInterval = 60 * 5;
  config.insertInterval = 60;
  config.enableTimestampJitter = true;
  
  StoreTestContoller testController(config);
  
  Store* store = new NarrowTableStore();
  testController.testAll(store);
  delete store;
}


////////////////////////////////////////////////
// NarrowTableStore
////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(EmptyTableStoreTest)
{
  DefaultStoreTestContollerConfig config;
  StoreTestContoller testController(config);

  Store* store = new EmptyStore();
  testController.testOnlyInsert(store);
  delete store;
}

////////////////////////////////////////////////
// RingMapStore
////////////////////////////////////////////////

/*
BOOST_AUTO_TEST_CASE(RingMapStoreTest)
{
 DefaultStoreTestContollerConfig config;
 StoreTestContoller testController(config);

  Store* store = new RingMapStore();
  testController.testAll(store);
  delete store;
}
*/

////////////////////////////////////////////////
// BeringeiStore
////////////////////////////////////////////////

#if defined(FOREMAN_ENABLE_BERINGEI)

/*
BOOST_AUTO_TEST_CASE(BeringeiStoreTest)
{
 DefaultStoreTestContollerConfig config;
 StoreTestContoller testController(config);

  Store* store = new BeringeiStore();
  testController.testAll(store);
  delete store;
}
*/

#endif

BOOST_AUTO_TEST_SUITE_END()
