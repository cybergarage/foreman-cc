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

#include <foreman/Metric.h>

using namespace Foreman;

BOOST_AUTO_TEST_CASE(NewMetricTest)
{
  Metric metric;

  BOOST_CHECK_EQUAL(metric.name.size(), 0);
}

BOOST_AUTO_TEST_CASE(NewMetricsTest)
{
  Metrics metrics;

  BOOST_CHECK_EQUAL(metrics.size(), 0);
}
