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

  Foreman::Error err;

  for (int n = 0; n < 100; n++) {
    std::stringstream ss;
    time_t ts;

    Object inObj;
    time(&ts);
    ts += rand();
    ss << ts;
    std::string key = "key" + ss.str();
    inObj.setKey(key);
    std::string val = "val" + ss.str();
    inObj.setData(val);

    BOOST_CHECK_EQUAL(store->size(), n);
    BOOST_CHECK_EQUAL(store->setObject(&inObj, &err), true);
    BOOST_CHECK_EQUAL(store->size(), (n + 1));

    Object outObj;

    BOOST_CHECK_EQUAL(store->getObject(key, &outObj, &err), true);
    BOOST_CHECK_EQUAL(inObj.equals(&outObj), true);
  }

  BOOST_CHECK(store->close());
}
