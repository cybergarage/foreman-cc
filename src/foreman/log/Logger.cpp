/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/log/Logger.h>

using namespace Foreman::Log;

////////////////////////////////////////////////
// GetSharedInstance
////////////////////////////////////////////////

static Logger gForemanLogSharedLogger;

Logger* Logger::GetSharedInstance()
{
  return &gForemanLogSharedLogger;
}

////////////////////////////////////////////////
// ForemanLoggerGetLevelString
////////////////////////////////////////////////

static std::string gFremanLogDebugMsg = "DEBUG";
static std::string gFremanLogTraceMsg = "TRACE";
static std::string gFremanLogInfoMsg = "INFO";
static std::string gFremanLogWarnMsg = "WARN";
static std::string gFremanLogErrorMsg = "ERROR";
static std::string gFremanLogFatalMsg = "FATAL";
static std::string gFremanLogUnkownMsg = "UNKNOWN";

static const char* ForemanLoggerGetLevelString(LogLevel level)
{
  switch (level) {
  case DBG:
    return gFremanLogDebugMsg.c_str();
  case TRACE:
    return gFremanLogTraceMsg.c_str();
  case INFO:
    return gFremanLogInfoMsg.c_str();
  case WARN:
    return gFremanLogWarnMsg.c_str();
  case ERROR:
    return gFremanLogErrorMsg.c_str();
  case FATAL:
    return gFremanLogFatalMsg.c_str();
  case NONE:
    return gFremanLogUnkownMsg.c_str();
  }
  return gFremanLogUnkownMsg.c_str();
}

////////////////////////////////////////////////
// Logger
////////////////////////////////////////////////

Logger::Logger()
{
  clear();
}

Logger::~Logger()
{
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

void Logger::clear()
{
  setLevel(INFO);
  OutputterList::clear();
}

////////////////////////////////////////////////
// debug
////////////////////////////////////////////////

size_t Logger::debug(const char* format, ...)
{
  va_list list;
  va_start(list, format);
  size_t n = message(Foreman::Log::DBG, format, list);
  va_end(list);
  return n;
}

////////////////////////////////////////////////
// trace
////////////////////////////////////////////////

size_t Logger::trace(const char* format, ...)
{
  va_list list;
  va_start(list, format);
  size_t n = message(Foreman::Log::TRACE, format, list);
  va_end(list);
  return n;
}

////////////////////////////////////////////////
// info
////////////////////////////////////////////////

size_t Logger::info(const char* format, ...)
{
  va_list list;
  va_start(list, format);
  size_t n = message(Foreman::Log::INFO, format, list);
  va_end(list);
  return n;
}

////////////////////////////////////////////////
// warn
////////////////////////////////////////////////

size_t Logger::warn(const char* format, ...)
{
  va_list list;
  va_start(list, format);
  size_t n = message(Foreman::Log::WARN, format, list);
  va_end(list);
  return n;
}

////////////////////////////////////////////////
// error
////////////////////////////////////////////////

size_t Logger::error(const char* format, ...)
{
  va_list list;
  va_start(list, format);
  size_t n = message(Foreman::Log::ERROR, format, list);
  va_end(list);
  return n;
}

////////////////////////////////////////////////
// fatal
////////////////////////////////////////////////

size_t Logger::fatal(const char* format, ...)
{
  va_list list;
  va_start(list, format);
  size_t n = message(Foreman::Log::FATAL, format, list);
  va_end(list);
  return n;
}

////////////////////////////////////////////////
// message
////////////////////////////////////////////////

#define MAX_LOG_BUF 2048

size_t Logger::message(LogLevel level, const char* format, ...)
{
  if (level < this->level)
    return 0;

  char msg[MAX_LOG_BUF], tsPrefix[MAX_LOG_BUF];

  time_t ts;
  struct tm* localts;
  ts = time(NULL);
  localts = localtime(&ts);

  strftime(tsPrefix, MAX_LOG_BUF, "%FT%T%z", localts);

  size_t prefixLen = snprintf(msg, MAX_LOG_BUF, "%s %s : ", tsPrefix, ForemanLoggerGetLevelString(level));

  va_list list;
  va_start(list, format);
  vsnprintf(msg + prefixLen, MAX_LOG_BUF - prefixLen, format, list);
  va_end(list);

  size_t nOutput = 0;
  for (auto& outputter : *this) {
    if (outputter->output(level, msg)) {
      nOutput++;
    }
  }

  return nOutput;
}
