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

BOOST_AUTO_TEST_CASE(ClangRegistryQuery)
{
  ForemanMetricQuery* q = foreman_registry_query_new();
  BOOST_CHECK(q);
  BOOST_CHECK(foreman_registry_query_delete(q));
}

BOOST_AUTO_TEST_SUITE_END()
