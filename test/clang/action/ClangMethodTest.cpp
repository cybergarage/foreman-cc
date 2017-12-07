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

BOOST_AUTO_TEST_CASE(NewMethod)
{
  ForemanActionMethod* method = foreman_action_method_new();
  BOOST_CHECK(method);
  BOOST_CHECK(foreman_action_method_delete(method));
}

BOOST_AUTO_TEST_SUITE_END()
