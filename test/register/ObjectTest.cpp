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
#include <stdio.h>

#include <foreman/register/Object.h>

#include "../ForemanTest.h"

using namespace Foreman::Register;

BOOST_AUTO_TEST_SUITE(register_)

BOOST_AUTO_TEST_CASE(Object)
{
  auto obj = new Object();
  delete obj;
}

BOOST_AUTO_TEST_SUITE_END()
