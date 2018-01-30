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

BOOST_AUTO_TEST_CASE(NewActionScriptManager)
{
  ForemanActionManager* mgr;

  mgr = foreman_action_manager_new();
  BOOST_CHECK(mgr);

  BOOST_CHECK(foreman_action_manager_delete(mgr));
}

BOOST_AUTO_TEST_SUITE_END()
