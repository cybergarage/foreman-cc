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
#include <foreman/Const.h>

#include "../ForemanTest.h"
#include "StoreTestController.h"

using namespace Foreman::Register;

////////////////////////////////////////////////
// StoreTestContoller
////////////////////////////////////////////////

StoreTestContoller::StoreTestContoller() {}

StoreTestContoller::~StoreTestContoller() {}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

void StoreTestContoller::run(Store* store)
{
  BOOST_CHECK(store->open());

  testRepeatInsert(store);
  testRepeatInsert(store);

  BOOST_CHECK(store->close());
}

////////////////////////////////////////////////
// testInsert
////////////////////////////////////////////////

void StoreTestContoller::testInsert(Store* store)
{
  BOOST_CHECK(store->clear());

  Foreman::Error err;

  for (int n = 0; n < 100; n++) {
    Object inObj;

    std::stringstream key;
    time_t ts;
    time(&ts);
    key << "key" << ts;
    inObj.setKey(key.str());

    std::stringstream val;
    key << "val" << ts;
    inObj.setData(val.str());

    BOOST_CHECK_EQUAL(store->size(), n);
    BOOST_CHECK_EQUAL(store->setObject(&inObj, &err), true);
    BOOST_CHECK_EQUAL(store->size(), (n + 1));

    Object outObj;

    BOOST_CHECK_EQUAL(store->getObject(key.str(), &outObj, &err), true);
    BOOST_CHECK_EQUAL(inObj.equals(&outObj), true);
    BOOST_CHECK_EQUAL(outObj.getVersion(), 1);
  }
}

////////////////////////////////////////////////
// testRepeatInsert
////////////////////////////////////////////////

void StoreTestContoller::testRepeatInsert(Store* store)
{
  BOOST_CHECK(store->clear());

  Foreman::Error err;

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      Object inObj;

      std::stringstream key;
      key << "rkey" << i;
      inObj.setKey(key.str());

      std::stringstream val;
      val << "rval" << i << j;
      inObj.setData(val.str());

      BOOST_CHECK_EQUAL(store->setObject(&inObj, &err), true);
      BOOST_CHECK_EQUAL(store->size(), (i + 1));

      Object outObj;

      BOOST_CHECK_EQUAL(store->getObject(key.str(), &outObj, &err), true);
      BOOST_CHECK_EQUAL(inObj.equals(&outObj), true);
      BOOST_CHECK_EQUAL(outObj.getVersion(), (j + 1));
    }
  }
}
