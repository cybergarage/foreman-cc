/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <foreman/metric/DataPoint.h>

using namespace Foreman::Metric;

BOOST_AUTO_TEST_SUITE(metric)

BOOST_AUTO_TEST_CASE(NewDataPointTest)
{
  DataPoint metric;
}

BOOST_AUTO_TEST_CASE(NewDataPointsTest)
{
  DataPoints metrics;

  BOOST_CHECK_EQUAL(metrics.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
