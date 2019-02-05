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

#include <cstdio>
#include <fstream>
#include <iostream>

#include <foreman/log/Logger.h>
#include <foreman/log/logger-c.h>

#include "../ForemanTest.h"
#include "LoggerTestController.h"

using namespace Foreman::Log;

BOOST_AUTO_TEST_SUITE(log)

BOOST_AUTO_TEST_CASE(NullOutputterTest)
{
  LoggerTestController testController;

  auto logger = new Logger();
  logger->addOutputter(new NullOutputter());
  testController.run(logger);
  delete logger;
}

BOOST_AUTO_TEST_CASE(StdOutputterTest)
{
  LoggerTestController testController;

  auto logger = new Logger();
  logger->addOutputter(new StdoutOutputter());
  testController.run(logger);
  delete logger;
}

BOOST_AUTO_TEST_CASE(FileOutputterTest)
{
  LoggerTestController testController;

  std::string logFilename = std::tmpnam(nullptr);

  auto logger = new Logger();
  logger->addOutputter(new FileOutputter(logFilename));
  testController.run(logger);
  delete logger;

  std::ifstream logFile(logFilename);
  BOOST_CHECK(logFile.good());

  if (logFile.good()) {
    size_t totalLogFileLines = 0;
    std::string line;
    while (getline(logFile, line)) {
      totalLogFileLines++;
    }
    BOOST_CHECK_EQUAL(testController.totalOutputMessages, totalLogFileLines);
  }
  BOOST_CHECK_EQUAL(std::remove(logFilename.c_str()), 0);
}

BOOST_AUTO_TEST_SUITE_END()
