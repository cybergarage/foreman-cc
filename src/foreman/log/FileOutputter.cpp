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
#include <fstream>

using namespace Foreman::Log;

////////////////////////////////////////////////
// FileOutputter
////////////////////////////////////////////////

FileOutputter::FileOutputter(std::string& filename)
{
  this->filename = filename;
}

FileOutputter::~FileOutputter()
{
}

////////////////////////////////////////////////
// output
////////////////////////////////////////////////

bool FileOutputter::output(LogLevel level, const char* msg)
{
  lock();

  std::ofstream ofs(this->filename, std::ios::app);
  if (!ofs) {
    unlock();
    return false;
  }

  ofs << msg << std::endl;

  unlock();

  return true;
}
