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
#include <fstream>
#else
#include <stdio.h>
#endif

using namespace Foreman::Log;

////////////////////////////////////////////////
// FileOutputter
////////////////////////////////////////////////

FileOutputter::FileOutputter(const std::string& filename)
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

#if defined(FOREMANCC_LOG_USESTDCXX)
  std::ofstream ofs(this->filename, std::ios::app);
  if (!ofs) {
    unlock();
    return false;
  }
  ofs << msg << std::endl;
#else
  auto fp = fopen(this->filename.c_str(), "a");
  if (!fp) {
    unlock();
    return false;
  }

  fprintf(fp, "%s\n", msg);
  fclose(fp);
#endif

  unlock();

  return true;
}
