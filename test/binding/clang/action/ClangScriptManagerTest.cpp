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
  auto TEST_METHOD_LANG = "python";
  auto TEST_METHOD_NAME = "qos_unsatisfied";
  auto TEST_METHOD_CODE = "import foreman\n"
                          "def qos_unsatisfied(params,results):\n"
                          "    foreman.set_register('qos', 'false')\n"
                          "    return True";

  auto err = foreman_error_new();
  auto inParams = foreman_action_parameters_new();
  auto outParams = foreman_action_parameters_new();

  // Setup

  auto mgr = foreman_action_manager_new();
  BOOST_CHECK(mgr);

  auto regstryStore = foreman_registry_store_new();
  BOOST_CHECK(foreman_action_manager_setregistrystore(mgr, regstryStore));

  auto regsterStore = foreman_register_store_new();
  BOOST_CHECK(foreman_action_manager_setregisterstore(mgr, regsterStore));

  // Check first method

  auto method = foreman_action_manager_getfirstmethod(mgr);
  BOOST_CHECK(!method);

  // Add a method

  method = foreman_action_method_new(TEST_METHOD_LANG);
  BOOST_CHECK(foreman_action_method_setname(method, TEST_METHOD_NAME));
  BOOST_CHECK(foreman_action_method_setstringcode(method, TEST_METHOD_CODE));
  BOOST_CHECK(foreman_action_manager_addmethod(mgr, method, err));

  // Check first method

  method = foreman_action_manager_getfirstmethod(mgr);
  BOOST_CHECK(method);

  method = foreman_action_manager_nextmethod(mgr, method);
  BOOST_CHECK(!method);

  // Exec the valid method

#if defined(FOREMAN_SUPPORT_PYTHON)
  BOOST_CHECK(foreman_action_manager_execmethod(mgr, TEST_METHOD_NAME, inParams, outParams, err));
#endif

  // Finalize

  BOOST_CHECK(foreman_action_manager_delete(mgr));

  BOOST_CHECK(foreman_registry_store_delete(regstryStore));
  BOOST_CHECK(foreman_register_store_delete(regsterStore));

  BOOST_CHECK(foreman_action_parameters_delete(inParams));
  BOOST_CHECK(foreman_action_parameters_delete(outParams));

  foreman_error_delete(err);
}

BOOST_AUTO_TEST_SUITE_END()
