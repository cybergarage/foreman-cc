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

using namespace Foreman::Log;

////////////////////////////////////////////////
// FileOutputter
////////////////////////////////////////////////

FileOutputter::FileOutputter()
{
}

FileOutputter::~FileOutputter()
{
}

////////////////////////////////////////////////
// output
////////////////////////////////////////////////

bool FileOutputter::output(LogLevel level, const char* msg)
{
  return false;
}
