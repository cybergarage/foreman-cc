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

BOOST_AUTO_TEST_CASE(NewMetricTest)
{
  Metric metric;

  BOOST_CHECK_EQUAL(metric.name.size(), 0);
}

BOOST_AUTO_TEST_CASE(NewMetricsTest)
{
  MetricArray metrics;

  BOOST_CHECK_EQUAL(metrics.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
