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

#include "../ForemanTest.h"
#include "LoggerTestController.h"

using namespace Foreman::Log;

////////////////////////////////////////////////
// LoggerTestController
////////////////////////////////////////////////

LoggerTestController::LoggerTestController() {}

LoggerTestController::~LoggerTestController() {}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

void LoggerTestController::run(Foreman::Log::Logger* logger)
{
  static const char* TEST_LOG_MSG_FORMAT = "%d";
  static const char* TEST_LOG_MSG_PARAM1 = "hello";

  LogLevel logLevels[] = { DBG, TRACE, INFO, WARN, ERROR, FATAL };

  this->totalOutputMessages = 0;

  size_t nOutputters = logger->size();
  size_t nLogLevels = sizeof(logLevels) / sizeof(logLevels[0]);

  for (size_t n = 0; n < nLogLevels; n++) {
    logger->setLevel(logLevels[n]);

    size_t outputMessages = 0;

    outputMessages += logger->debug(TEST_LOG_MSG_FORMAT, TEST_LOG_MSG_PARAM1, n);
    outputMessages += logger->trace(TEST_LOG_MSG_FORMAT, TEST_LOG_MSG_PARAM1, n);
    outputMessages += logger->info(TEST_LOG_MSG_FORMAT, TEST_LOG_MSG_PARAM1, n);
    outputMessages += logger->warn(TEST_LOG_MSG_FORMAT, TEST_LOG_MSG_PARAM1, n);
    outputMessages += logger->error(TEST_LOG_MSG_FORMAT, TEST_LOG_MSG_PARAM1, n);
    outputMessages += logger->fatal(TEST_LOG_MSG_FORMAT, TEST_LOG_MSG_PARAM1, n);

    BOOST_CHECK_EQUAL(outputMessages, ((nLogLevels - n) * nOutputters));

    this->totalOutputMessages += outputMessages;
  }
}
