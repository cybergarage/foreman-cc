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

#include <foreman/foreman-c.h>

BOOST_AUTO_TEST_SUITE(log)

BOOST_AUTO_TEST_CASE(LoggerFunc)
{
  auto logger = foreman_logger_new();

  BOOST_CHECK(foreman_logger_setlevel(logger, FOREMANCC_LOGGER_LEVEL_ALL));

  BOOST_CHECK_EQUAL(foreman_logger_info(logger, ""), 0);
  BOOST_CHECK_EQUAL(foreman_logger_debug(logger, ""), 0);
  BOOST_CHECK_EQUAL(foreman_logger_error(logger, ""), 0);
  BOOST_CHECK_EQUAL(foreman_logger_warn(logger, ""), 0);
  BOOST_CHECK_EQUAL(foreman_logger_trace(logger, ""), 0);

  BOOST_CHECK(foreman_logger_addnulloutputter(logger));

  BOOST_CHECK_EQUAL(foreman_logger_info(logger, ""), 1);
  BOOST_CHECK_EQUAL(foreman_logger_debug(logger, ""), 1);
  BOOST_CHECK_EQUAL(foreman_logger_error(logger, ""), 1);
  BOOST_CHECK_EQUAL(foreman_logger_warn(logger, ""), 1);
  BOOST_CHECK_EQUAL(foreman_logger_trace(logger, ""), 1);

  foreman_logger_delete(logger);
}

BOOST_AUTO_TEST_SUITE_END()
