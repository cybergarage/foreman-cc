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
    static Logger* GetSharedInstance();

public:
    Logger();
    ~Logger();

    size_t message(LogLevel level, const char* format, ...);
  };
}
}

#if defined(__USE_ISOC99)
#if defined(DEBUG)
#define FOREMAN_LOG_DEBUG(format, ...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::DEBUG, format, __VA_ARGS__)
#else
#define FOREMAN_LOG_ERROR(format, ...)
#endif
#define FOREMAN_LOG_TRACE(format, ...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::TRACE, format, __VA_ARGS__)
#define FOREMAN_LOG_INFO(format, ...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::INFO, format, __VA_ARGS__)
#define FOREMAN_LOG_WARN(format, ...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::WARN, format, __VA_ARGS__)
#define FOREMAN_LOG_ERROR(format, ...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::ERROR, format, __VA_ARGS__)
#else
#if defined(DEBUG)
#define FOREMAN_LOG_DEBUG(format...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::DEBUG, format, __VA_ARGS__)
#else
#define FOREMAN_LOG_ERROR(format...)
#endif
#define FOREMAN_LOG_TRACE(format...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::TRACE, format, __VA_ARGS__)
#define FOREMAN_LOG_INFO(format...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::INFO, format, __VA_ARGS__)
#define FOREMAN_LOG_WARN(format...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::WARN, format, __VA_ARGS__)
#define FOREMAN_LOG_ERROR(format...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::ERROR, format, __VA_ARGS__)
#endif

#endif
