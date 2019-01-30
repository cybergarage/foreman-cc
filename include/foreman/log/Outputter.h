/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_LOG_OUTPUTTER_H_
#define _FOREMANCC_LOG_OUTPUTTER_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <memory>
#include <vector>

#include <foreman/util/Mutex.h>
#include <foreman/log/Level.h>

namespace Foreman {
namespace Log {

  ////////////////////////////////////////////////
  // Outputter
  ////////////////////////////////////////////////

  class Outputter : public Mutex {

public:
    Outputter();
    ~Outputter();

    virtual bool output(LogLevel level, const char* msg) = 0;
  };

  ////////////////////////////////////////////////
  // Outputter
  ////////////////////////////////////////////////

  class OutputterList : public std::vector<std::unique_ptr<Outputter>> {

public:
    OutputterList();
    ~OutputterList();

    void addOutputter(Outputter* outputter);
  };

  ////////////////////////////////////////////////
  // Outputter
  ////////////////////////////////////////////////

  class StdoutOutputter : public Outputter {

public:
    StdoutOutputter();
    ~StdoutOutputter();

    bool output(LogLevel level, const char* msg);
  };

  ////////////////////////////////////////////////
  // Outputter
  ////////////////////////////////////////////////

  class FileOutputter : public Outputter {

public:
    FileOutputter();
    ~FileOutputter();

    bool output(LogLevel level, const char* msg);
  };
}
}

#endif
