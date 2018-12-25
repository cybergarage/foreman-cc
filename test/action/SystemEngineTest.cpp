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

#include "ManagerTestController.h"
#include <foreman/action/impl/System.h>

BOOST_AUTO_TEST_SUITE(action)

BOOST_AUTO_TEST_CASE(SystemEngine)
{
  Foreman::Error err;
  Foreman::Action::Manager mgr;
  Foreman::Action::ManagerTestController testController;

  mgr.addEngine(new Foreman::Action::SystemEngine());

  static const char* ECHO_CODE = "echo";

  auto echo = new Foreman::Action::SystemMethod();
  BOOST_CHECK(echo->setName(FOREMANCC_TEST_SCRIPT_ECHO_METHOD));
  BOOST_CHECK(echo->setCode(ECHO_CODE));
  BOOST_CHECK(mgr.addMethod(echo, &err));

  testController.testEcho(&mgr, false);
}

BOOST_AUTO_TEST_SUITE_END()
