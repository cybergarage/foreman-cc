/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <foreman/DataPoint.h>

using namespace Foreman;

BOOST_AUTO_TEST_CASE(NewDataPointTest)
{
  DataPoint metric;
}

BOOST_AUTO_TEST_CASE(NewDataPointsTest)
{
  DataPoints metrics;

  BOOST_CHECK_EQUAL(metrics.size(), 0);
}
