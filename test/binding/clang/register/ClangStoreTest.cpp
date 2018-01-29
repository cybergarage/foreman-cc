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

BOOST_AUTO_TEST_CASE(NewRegisterSQLiteStore)
{
  ForemanRegisterStore* store = foreman_register_store_new();
  BOOST_CHECK(store);
  BOOST_CHECK(foreman_register_store_delete(store));
}

BOOST_AUTO_TEST_SUITE_END()
