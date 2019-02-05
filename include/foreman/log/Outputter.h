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
#include <string>
#include <vector>

#include <foreman/log/Level.h>
#include <foreman/util/Mutex.h>

namespace Foreman {
namespace Log {

  ////////////////////////////////////////////////
  // Outputter
  ////////////////////////////////////////////////

  class Outputter : public Mutex {

public:
    Outputter();
    virtual ~Outputter();

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
  // StdoutOutputter
  ////////////////////////////////////////////////

  class StdoutOutputter : public Outputter {

public:
    StdoutOutputter();
    ~StdoutOutputter();

    bool output(LogLevel level, const char* msg);
  };

  ////////////////////////////////////////////////
  // FileOutputter
  ////////////////////////////////////////////////

  class FileOutputter : public Outputter {

public:
    FileOutputter(const std::string& filename);
    ~FileOutputter();

    const char* getFilename()
    {
      return this->filename.c_str();
    }

    bool output(LogLevel level, const char* msg);

private:
    std::string filename;
  };

  ////////////////////////////////////////////////
  // NullOutputter
  ////////////////////////////////////////////////

  class NullOutputter : public Outputter {

public:
    NullOutputter() {}
    ~NullOutputter() {}

    bool output(LogLevel level, const char* msg)
    {
      return true;
    }
  };
}
}

#endif
