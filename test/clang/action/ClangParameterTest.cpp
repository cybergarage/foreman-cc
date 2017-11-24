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

BOOST_AUTO_TEST_CASE(NewActionParameter)
{
  ForemanActionParameter* param = foreman_action_parameter_new();
  BOOST_CHECK(param);
  BOOST_CHECK(foreman_action_parameter_delete(param));
}

BOOST_AUTO_TEST_CASE(NewActionParameters)
{
  ForemanActionParameters* params = foreman_action_parameters_new();
  BOOST_CHECK(params);
  BOOST_CHECK(foreman_action_parameters_delete(params));
}

BOOST_AUTO_TEST_SUITE_END()
