/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_TEST_LOGGERTESTCONTROLLER_H_
#define _FOREMANCC_TEST_LOGGERTESTCONTROLLER_H_

#include <foreman/log/Logger.h>

class LoggerTestController {
  public:
  LoggerTestController();
  ~LoggerTestController();

  void run(Foreman::Log::Logger* logger);

  size_t totalOutputMessages;
};

#endif
