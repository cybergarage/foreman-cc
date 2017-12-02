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

using namespace Foreman::Action;

BOOST_AUTO_TEST_SUITE(action)

BOOST_AUTO_TEST_CASE(PythonEngine)
{
  PythonEngine* engine = new PythonEngine();
  delete engine;
}

BOOST_AUTO_TEST_SUITE_END()
