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
// SharedInstance
////////////////////////////////////////////////

static Logger gForemanLogDefaultLogger;
static Logger* gForemanLogSharedLogger = &gForemanLogDefaultLogger;

void Logger::SetSharedInstance(Logger* logger)
{
  gForemanLogSharedLogger = logger;
}

Logger* Logger::GetSharedInstance()
{
  return gForemanLogSharedLogger;
}

////////////////////////////////////////////////
// ForemanLoggerGetLevelString
////////////////////////////////////////////////

static const char* ForemanLoggerGetLevelString(LogLevel level)
{
  switch (level) {
  case DBG:
    return FOREMANCC_LOGGER_LEVEL_STRING_DEBUG;
  case TRACE:
    return FOREMANCC_LOGGER_LEVEL_STRING_TRACE;
  case INFO:
    return FOREMANCC_LOGGER_LEVEL_STRING_INFO;
  case WARN:
    return FOREMANCC_LOGGER_LEVEL_STRING_WARN;
  case ERROR:
    return FOREMANCC_LOGGER_LEVEL_STRING_ERROR;
  case FATAL:
    return FOREMANCC_LOGGER_LEVEL_STRING_FATAL;
  case NONE:
    return "";
  }
  return "";
}

////////////////////////////////////////////////
// ForemanLoggerGetStringLevel
////////////////////////////////////////////////

static LogLevel ForemanLoggerGetStringLevel(const std::string& levelString)
{
  if (levelString.compare(FOREMANCC_LOGGER_LEVEL_STRING_DEBUG) == 0)
    return DBG;
  if (levelString.compare(FOREMANCC_LOGGER_LEVEL_STRING_TRACE) == 0)
    return TRACE;
  if (levelString.compare(FOREMANCC_LOGGER_LEVEL_STRING_INFO) == 0)
    return INFO;
  if (levelString.compare(FOREMANCC_LOGGER_LEVEL_STRING_WARN) == 0)
    return WARN;
  if (levelString.compare(FOREMANCC_LOGGER_LEVEL_STRING_ERROR) == 0)
    return ERROR;
  if (levelString.compare(FOREMANCC_LOGGER_LEVEL_STRING_FATAL) == 0)
    return FATAL;
  return NONE;
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

bool Logger::setLevelString(const std::string& levelString)
{
  auto level = ForemanLoggerGetStringLevel(levelString);
  if (level == NONE)
    return false;
  setLevel(level);
  return true;
}

////////////////////////////////////////////////
// debug
////////////////////////////////////////////////

const char* Logger::getLevelString()
{
  return ForemanLoggerGetLevelString(this->level);
}

////////////////////////////////////////////////
// debug
////////////////////////////////////////////////

size_t Logger::debug(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  size_t n = message(Foreman::Log::DBG, format, args);
  va_end(args);
  return n;
}

////////////////////////////////////////////////
// trace
////////////////////////////////////////////////

size_t Logger::trace(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  size_t n = message(Foreman::Log::TRACE, format, args);
  va_end(args);
  return n;
}

////////////////////////////////////////////////
// info
////////////////////////////////////////////////

size_t Logger::info(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  size_t n = message(Foreman::Log::INFO, format, args);
  va_end(args);
  return n;
}

////////////////////////////////////////////////
// warn
////////////////////////////////////////////////

size_t Logger::warn(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  size_t n = message(Foreman::Log::WARN, format, args);
  va_end(args);
  return n;
}

////////////////////////////////////////////////
// error
////////////////////////////////////////////////

size_t Logger::error(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  size_t n = message(Foreman::Log::ERROR, format, args);
  va_end(args);
  return n;
}

////////////////////////////////////////////////
// fatal
////////////////////////////////////////////////

size_t Logger::fatal(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  size_t n = message(Foreman::Log::FATAL, format, args);
  va_end(args);
  return n;
}

////////////////////////////////////////////////
// message
////////////////////////////////////////////////

size_t Logger::message(LogLevel level, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  size_t n = message(level, format, args);
  va_end(args);
  return n;
}

////////////////////////////////////////////////
// message
////////////////////////////////////////////////

#define MAX_LOG_BUF 2048

size_t Logger::message(LogLevel level, const char* format, va_list args)
{
  if (level < this->level)
    return 0;

  char msg[MAX_LOG_BUF], tsPrefix[MAX_LOG_BUF];

  time_t ts;
  struct tm* localts;
  ts = time(NULL);
  localts = localtime(&ts);

  strftime(tsPrefix, MAX_LOG_BUF, "%FT%T%z", localts);

  size_t prefixLen = snprintf(msg, MAX_LOG_BUF, "%s %-5s : ", tsPrefix, ForemanLoggerGetLevelString(level));

  vsnprintf(msg + prefixLen, MAX_LOG_BUF - prefixLen, format, args);

  size_t nOutput = 0;
  for (auto& outputter : *this) {
    if (outputter->output(level, msg)) {
      nOutput++;
    }
  }

  return nOutput;
}
