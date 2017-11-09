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
  createHierarchicalObjects(store);
  
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

    // Insert a same object
    BOOST_CHECK(!store->createObject(&obj, &err));
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


////////////////////////////////////////////////
// createHierarchicalObjects
////////////////////////////////////////////////

void StoreTestContoller::createHierarchicalObjects(Store* store)
{
  BOOST_CHECK(store->clear());
  
  Query q;
  Foreman::Error err;
  Objects objs;
  char objId[32];
  char parentId[32];
  char name[32];
  char data[32];
  
  q.setParentId(FOREMANCC_REGISTRY_ROOT_OBJECT_ID);
  objs.clear();
  BOOST_CHECK(store->browse(&q, &objs, &err));
  BOOST_CHECK_EQUAL(objs.size(), 0);
  
  // Insert
  
  strcpy(parentId, FOREMANCC_REGISTRY_ROOT_OBJECT_ID);

  for (size_t n = 1; n <= FORMANCC_TEST_LOOP_DEFAULT; n++) {
    snprintf(objId, sizeof(name), "id%ld", n);
    snprintf(name, sizeof(name), "name%ld", n);
    snprintf(data, sizeof(data), "data%ld", n);
    
    Object obj;
    obj.setId(objId);
    obj.setName(name);
    obj.setData(data);

    // insert an invalid object whose parent object is not found
    obj.setParentId(objId);
    BOOST_CHECK(!store->createObject(&obj, &err));
    
    // insert a valid object
    obj.setParentId(parentId);
    BOOST_CHECK(store->createObject(&obj, &err));

    // Insert a same object
    BOOST_CHECK(!store->createObject(&obj, &err));
    
    strcpy(parentId, objId);
  }
  
  // Get
  
  strcpy(parentId, FOREMANCC_REGISTRY_ROOT_OBJECT_ID);
  
  for (size_t n = 1; n <= FORMANCC_TEST_LOOP_DEFAULT; n++) {
    objs.clear();
    q.setParentId(parentId);
    BOOST_CHECK(store->browse(&q, &objs, &err));
    BOOST_CHECK_EQUAL(objs.size(), 1);
    
    snprintf(objId, sizeof(name), "id%ld", n);
    
    Object obj;
    BOOST_CHECK(store->getObject(objId, &obj, &err));
    BOOST_CHECK_EQUAL(obj.getParentId(), parentId);
    
    strcpy(parentId, objId);
  }

  // Delete
  
  for (size_t n = FORMANCC_TEST_LOOP_DEFAULT; 1 <= n; n--) {
    snprintf(objId, sizeof(name), "id%ld", n);

    objs.clear();
    q.setParentId(objId);
    BOOST_CHECK(store->browse(&q, &objs, &err));
    BOOST_CHECK_EQUAL(objs.size(), 0);
    
    Object obj;
    BOOST_CHECK(store->deleteObject(objId, &err));
  }

  BOOST_CHECK(store->clear());
}

