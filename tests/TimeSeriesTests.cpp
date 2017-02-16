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

#include <foreman/TimeSeries.h>

using namespace Foreman;

BOOST_AUTO_TEST_CASE(NewTimeSeriesTest)
{
  TimeSeries ts;

  BOOST_CHECK_EQUAL(ts.name.size(), 0);
}
