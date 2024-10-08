/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_LOG_LOGGER_H_
#define _FOREMANCC_LOG_LOGGER_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>
#include <time.h>

#include <stdarg.h>

#include <foreman/log/Level.h>
#include <foreman/log/Outputter.h>

namespace Foreman {
namespace Log {

  ////////////////////////////////////////////////
  // Logger
  ////////////////////////////////////////////////

  class Logger : public OutputterList {

public:
    static void SetSharedInstance(Logger* logger);
    static Logger* GetSharedInstance();

public:
    Logger();
    ~Logger();

    void setLevel(LogLevel level)
    {
      this->level = level;
    }

    LogLevel getLevel()
    {
      return this->level;
    }

    bool setLevelString(const std::string& levelString);
    const char* getLevelString();

    size_t error(const char* format, ...);
    size_t warn(const char* format, ...);
    size_t info(const char* format, ...);
    size_t trace(const char* format, ...);
    size_t debug(const char* format, ...);
    size_t fatal(const char* format, ...);

    size_t message(LogLevel level, const char* format, ...);

    void clear();

private:
    size_t message(LogLevel level, const char* format, va_list args);

private:
    LogLevel level;
  };
}
}

#endif
