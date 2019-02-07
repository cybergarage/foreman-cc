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

BOOST_AUTO_TEST_SUITE(logger)

BOOST_AUTO_TEST_CASE(LevelStringsTest)
{
  Logger logger;

  BOOST_CHECK(logger.setLevelString(FOREMANCC_LOGGER_LEVEL_STRING_DEBUG));
  BOOST_CHECK_EQUAL(logger.getLevel(), DBG);
  BOOST_CHECK_EQUAL(logger.getLevelString(), FOREMANCC_LOGGER_LEVEL_STRING_DEBUG);

  BOOST_CHECK(logger.setLevelString(FOREMANCC_LOGGER_LEVEL_STRING_TRACE));
  BOOST_CHECK_EQUAL(logger.getLevel(), TRACE);
  BOOST_CHECK_EQUAL(logger.getLevelString(), FOREMANCC_LOGGER_LEVEL_STRING_TRACE);

  BOOST_CHECK(logger.setLevelString(FOREMANCC_LOGGER_LEVEL_STRING_INFO));
  BOOST_CHECK_EQUAL(logger.getLevel(), INFO);
  BOOST_CHECK_EQUAL(logger.getLevelString(), FOREMANCC_LOGGER_LEVEL_STRING_INFO);

  BOOST_CHECK(logger.setLevelString(FOREMANCC_LOGGER_LEVEL_STRING_WARN));
  BOOST_CHECK_EQUAL(logger.getLevel(), WARN);
  BOOST_CHECK_EQUAL(logger.getLevelString(), FOREMANCC_LOGGER_LEVEL_STRING_WARN);

  BOOST_CHECK(logger.setLevelString(FOREMANCC_LOGGER_LEVEL_STRING_ERROR));
  BOOST_CHECK_EQUAL(logger.getLevel(), ERROR);
  BOOST_CHECK_EQUAL(logger.getLevelString(), FOREMANCC_LOGGER_LEVEL_STRING_ERROR);

  BOOST_CHECK(logger.setLevelString(FOREMANCC_LOGGER_LEVEL_STRING_FATAL));
  BOOST_CHECK_EQUAL(logger.getLevel(), FATAL);
  BOOST_CHECK_EQUAL(logger.getLevelString(), FOREMANCC_LOGGER_LEVEL_STRING_FATAL);
}

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
  // Disable not to oup
  //testController.run(logger);
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

BOOST_AUTO_TEST_CASE(MultipleOutputtersTest)
{
  LoggerTestController testController;

  std::string logFilename = std::tmpnam(nullptr);

  auto logger = new Logger();
  logger->addOutputter(new NullOutputter());
  logger->addOutputter(new FileOutputter(logFilename));
  testController.run(logger);
  delete logger;

  BOOST_CHECK_EQUAL(std::remove(logFilename.c_str()), 0);
}

BOOST_AUTO_TEST_SUITE_END()
