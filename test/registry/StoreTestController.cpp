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
  createRootObjects(store);

  BOOST_CHECK(store->close());
}

////////////////////////////////////////////////
// createInvalidObjects
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

////////////////////////////////////////////////
// createRootObjects
////////////////////////////////////////////////

void StoreTestContoller::createRootObjects(Store* store)
{
  BOOST_CHECK(store->clear());

  Query q;
  Foreman::Error err;
  Objects objs;
  char name[32];
  char data[32];

  q.setParentId(FOREMANCC_REGISTRY_ROOT_OBJECT_ID);
  objs.clear();
  BOOST_CHECK(store->browse(&q, &objs, &err));
  BOOST_CHECK_EQUAL(objs.size(), 0);
  
  // Insert

  for (size_t n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    snprintf(name, sizeof(name), "name%ld", n);
    snprintf(data, sizeof(data), "data%ld", n);

    Object obj;
    obj.setParentId(FOREMANCC_REGISTRY_ROOT_OBJECT_ID);
    obj.setName(name);
    obj.setData(data);
    BOOST_CHECK(store->createObject(&obj, &err));
  }

  // Get

  q.setParentId(FOREMANCC_REGISTRY_ROOT_OBJECT_ID);
  objs.clear();
  BOOST_CHECK(store->browse(&q, &objs, &err));
  BOOST_CHECK_EQUAL(objs.size(), FORMANCC_TEST_LOOP_DEFAULT);

  for (size_t n = 0; n < objs.size(); n++) {
    Object* browseObj = objs.getObject(n);
    BOOST_CHECK(browseObj);
    BOOST_CHECK(browseObj->isRootParentId());
    snprintf(name, sizeof(name), "name%ld", n);
    snprintf(data, sizeof(data), "data%ld", n);

    Object fetchObj;
    BOOST_CHECK(store->getObject(browseObj->getId(), &fetchObj, &err));
    BOOST_CHECK(browseObj->equals(&fetchObj));
  }

  // Delete
  
  q.setParentId(FOREMANCC_REGISTRY_ROOT_OBJECT_ID);
  objs.clear();
  BOOST_CHECK(store->browse(&q, &objs, &err));
  BOOST_CHECK_EQUAL(objs.size(), FORMANCC_TEST_LOOP_DEFAULT);
  
  for (size_t n = 0; n < objs.size(); n++) {
    Object* browseObj = objs.getObject(n);
    BOOST_CHECK(store->deleteObject(browseObj->getId(), &err));

    Object fetchObj;
    BOOST_CHECK(!store->getObject(browseObj->getId(), &fetchObj, &err));
  }

  q.setParentId(FOREMANCC_REGISTRY_ROOT_OBJECT_ID);
  objs.clear();
  BOOST_CHECK(store->browse(&q, &objs, &err));
  BOOST_CHECK_EQUAL(objs.size(), 0);
  
  BOOST_CHECK(store->clear());
}
