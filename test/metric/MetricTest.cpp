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

#include <foreman/metric/Metric.h>

using namespace Foreman::Metric;

BOOST_AUTO_TEST_SUITE(metric)

BOOST_AUTO_TEST_CASE(MetricTest)
{
  Metric m;
}

BOOST_AUTO_TEST_CASE(MetricsMapTest)
{
  MetricMap mmap;

  BOOST_CHECK_EQUAL(mmap.size(), 0);
}

BOOST_AUTO_TEST_CASE(MetricsArrayTest)
{
  MetricArray metrics;

  BOOST_CHECK_EQUAL(metrics.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
