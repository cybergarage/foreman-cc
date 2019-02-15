/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/log/Outputter.h>

#if defined(FOREMANCC_LOG_USESTDCXX)
#include <iostream>
#else
#include <stdio.h>
#endif

using namespace Foreman::Log;

////////////////////////////////////////////////
// StdoutOutputter
////////////////////////////////////////////////

StdoutOutputter::StdoutOutputter()
{
}

StdoutOutputter::~StdoutOutputter()
{
}

////////////////////////////////////////////////
// output
////////////////////////////////////////////////

bool StdoutOutputter::output(LogLevel level, const char* msg)
{
  lock();

#if defined(FOREMANCC_LOG_USESTDCXX)
  std::cout << msg << std::endl;
#else
  printf("%s\n", msg);
#endif

  unlock();

  return true;
}
