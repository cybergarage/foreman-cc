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
#include <iostream>

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
  
  std::cout << msg << std::endl;
 
  unlock();
  
  return true;
}
