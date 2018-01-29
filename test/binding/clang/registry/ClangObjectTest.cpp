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

#include <foreman/foreman-c.h>

BOOST_AUTO_TEST_SUITE(clang)

BOOST_AUTO_TEST_CASE(NewRegistryObject)
{
  ForemanRegistryObject* obj = foreman_registry_object_new();
  BOOST_CHECK(obj);
  BOOST_CHECK(foreman_registry_object_delete(obj));
}

BOOST_AUTO_TEST_CASE(NewRegistryObjects)
{
  ForemanRegistryObjects* objs = foreman_registry_objects_new();
  BOOST_CHECK(objs);
  BOOST_CHECK(foreman_registry_objects_delete(objs));
}

BOOST_AUTO_TEST_SUITE_END()
