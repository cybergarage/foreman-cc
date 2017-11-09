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

#include "StoreTestController.h"

using namespace Foreman::Registry;

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
  BOOST_CHECK(store->isOpened());
  
  createInvalidObjects(store);
  
  BOOST_CHECK(store->close());
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

void StoreTestContoller::createInvalidObjects(Store* store)
{
  BOOST_CHECK(store->clear());

  Foreman::Error err;
  
  Object obj;
  BOOST_CHECK(!store->createObject(&obj, &err));

  obj.setName("object");
  BOOST_CHECK(!store->createObject(&obj, &err));

  obj.setParentId(FOREMANCC_REGISTRY_ROOT_OBJECT_ID);
  BOOST_CHECK(store->createObject(&obj, &err));

  BOOST_CHECK(store->deleteObject(obj.getId(), &err));
  
  BOOST_CHECK(store->clear());
}
