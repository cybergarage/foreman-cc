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
#include <string>
#include <vector>

#include <foreman/Platform.h>
#include <foreman/foreman-c.h>

#if defined(FOREMAN_SUPPORT_PYTHON)
#include <foreman/action/impl/Python.h>
#endif

BOOST_AUTO_TEST_SUITE(clang)

BOOST_AUTO_TEST_CASE(ScriptManagerPythonActions)
{
  auto TEST_METHOD_LANG = "python";
  std::vector<std::string> TEST_METHOD_NAMES = {
    "echo",
    "qos_unsatisfied"
  };
  std::vector<std::string> TEST_METHOD_CODES = {
    "import foreman\n"
    "def echo(params,results):\n"
  	"    for key, value in params.items():\n"
		"        results[key] = value\n"
	  "    return True",
    "import foreman\n"
    "def qos_unsatisfied(params,results):\n"
    "    foreman.set_register('qos', 'false')\n"
    "    return True"
  };

  // Setup

  auto mgr = foreman_action_manager_new();
  BOOST_CHECK(mgr);

  auto regsterStore = foreman_register_store_new();
  BOOST_CHECK(foreman_action_manager_setregisterstore(mgr, regsterStore));

  // Check first method

  auto method = foreman_action_manager_getfirstmethod(mgr);
  BOOST_CHECK(!method);

  // Add methods

  for (size_t n = 0; n < TEST_METHOD_NAMES.size(); n++) {
    auto err = foreman_error_new();
    method = foreman_action_method_new(TEST_METHOD_LANG);
    BOOST_CHECK(foreman_action_method_setname(method, TEST_METHOD_NAMES[n].c_str()));
    BOOST_CHECK(foreman_action_method_setstringcode(method, TEST_METHOD_CODES[n].c_str()));
    BOOST_CHECK(foreman_action_manager_addmethod(mgr, method, err));
    foreman_error_delete(err);
  }

  // Exec methods
  for (size_t n = 0; n < TEST_METHOD_NAMES.size(); n++) {
      auto inParams = foreman_action_parameters_new();
#if defined(FOREMAN_SUPPORT_PYTHON)
    for (auto loop = 0; loop < 10; loop++) {
      auto err = foreman_error_new();
      auto outParams = foreman_action_parameters_new();
      BOOST_CHECK(foreman_action_manager_execmethod(mgr, TEST_METHOD_NAMES[n].c_str(), inParams, outParams, err));
      BOOST_CHECK(foreman_error_delete(err));
      BOOST_CHECK(foreman_action_parameters_delete(outParams));
    }
#endif
      BOOST_CHECK(foreman_action_parameters_delete(inParams));
  }

  // Finalize

  BOOST_CHECK(foreman_action_manager_delete(mgr));
  BOOST_CHECK(foreman_register_store_delete(regsterStore));
}

BOOST_AUTO_TEST_SUITE_END()
