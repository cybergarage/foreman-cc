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

BOOST_AUTO_TEST_CASE(NewRegistryProperty)
{
  ForemanRegistryProperty* prop = foreman_registry_property_new();
  BOOST_CHECK(prop);
  BOOST_CHECK(foreman_registry_property_delete(prop));
}

BOOST_AUTO_TEST_CASE(NewRegistryProperties)
{
  ForemanRegistryProperties* props = foreman_registry_properties_new();
  BOOST_CHECK(props);
  BOOST_CHECK(foreman_registry_properties_delete(props));
}

BOOST_AUTO_TEST_SUITE_END()
