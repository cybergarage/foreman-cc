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

  auto err = foreman_error_new();
  
  // Check first method
  
  auto method = foreman_action_manager_getfirstmethod(mgr);
  BOOST_CHECK(!method);

  // Add a method
  
  method = foreman_action_method_new("");
  BOOST_CHECK(foreman_action_method_setname(method, "test"));
  BOOST_CHECK(foreman_action_manager_addmethod(mgr, method, err));

  // Check first method

  method = foreman_action_manager_getfirstmethod(mgr);
  BOOST_CHECK(method);
  
  method = foreman_action_manager_nextmethod(mgr, method);
  BOOST_CHECK(!method);
  
  foreman_error_delete(err);
              
  BOOST_CHECK(foreman_action_manager_delete(mgr));
}

BOOST_AUTO_TEST_SUITE_END()
