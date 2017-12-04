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

#include <foreman/action/Script.h>
#include <foreman/action/impl/Python.h>

BOOST_AUTO_TEST_SUITE(action)
BOOST_AUTO_TEST_SUITE(python)

#if defined(FOREMAN_SUPPORT_PYTHON)

BOOST_AUTO_TEST_CASE(PythonEngine)
{
  PythonEngine* engine = new PythonEngine();
  delete engine;
}

BOOST_AUTO_TEST_CASE(PythonParameters)
{
  Foreman::Action::Parameters params;

  Foreman::Action::PythonParameters pyInParams;
  BOOST_CHECK(pyInParams.set(&params));
  BOOST_CHECK(pyInParams.equals(&params));

  Foreman::Action::PythonParameters pyOutParams;
  BOOST_CHECK(pyOutParams.get(&params));
  BOOST_CHECK(pyOutParams.equals(&params));
}

#endif

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
