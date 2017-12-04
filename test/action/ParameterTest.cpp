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

#include <foreman/action/Parameter.h>

using namespace Foreman::Action;

BOOST_AUTO_TEST_SUITE(action)

BOOST_AUTO_TEST_CASE(NewParameter)
{
  Integer ivalue;
  BOOST_CHECK(ivalue.isInteger());

  Real rvalue;
  BOOST_CHECK(rvalue.isReal());

  String svalue;
  BOOST_CHECK(svalue.isString());

  Bool bvalue;
  BOOST_CHECK(bvalue.isBool());
}

BOOST_AUTO_TEST_SUITE_END()
