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

#include <foreman/util/Mutex.h>

using namespace Foreman;

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(MutexTest)
{
  Mutex* mutex = new Mutex();
  BOOST_CHECK_EQUAL(mutex->lock(), true);
  BOOST_CHECK_EQUAL(mutex->unlock(), true);
  delete mutex;
}

BOOST_AUTO_TEST_SUITE_END()
