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

#include <foreman/metric/impl/TimeSeries.h>

using namespace Foreman::Metric;

BOOST_AUTO_TEST_SUITE(metric)

BOOST_AUTO_TEST_CASE(NewTimeSeriesTest)
{
}

BOOST_AUTO_TEST_CASE(NewTimeSeriesMap)
{
  TimeSeriesMap tsMap;

  BOOST_CHECK_EQUAL(tsMap.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
