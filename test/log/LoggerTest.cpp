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
#include <stdio.h>

#include <foreman/log/Logger.h>
#include <foreman/log/logger-c.h>

#include "../ForemanTest.h"

using namespace Foreman::Log;

BOOST_AUTO_TEST_SUITE(log)

BOOST_AUTO_TEST_CASE(Log)
{
  auto logger = Logger::GetSharedInstance();
  logger->addOutputter(new StdoutOutputter());
  foreman_log_info("%s", "hello");
}

BOOST_AUTO_TEST_SUITE_END()
