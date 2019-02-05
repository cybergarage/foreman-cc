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
// GetLevelString
////////////////////////////////////////////////

static std::string gFremanLogDebugMsg = "DEBUG";
static std::string gFremanLogTraceMsg = "TRACE";
static std::string gFremanLogInfoMsg = "INFO";
static std::string gFremanLogWarnMsg = "WARN";
static std::string gFremanLogErrorMsg = "ERROR";
static std::string gFremanLogUnkownMsg = "UNKNOWN";

static const char* gForemanLoggerGetLevelString(LogLevel level)
{
  switch (level) {
  case TRACE:
    return gFremanLogTraceMsg.c_str();
  case DEBUG:
    return gFremanLogDebugMsg.c_str();
  case INFO:
    return gFremanLogInfoMsg.c_str();
  case WARN:
    return gFremanLogWarnMsg.c_str();
  case ERROR:
    return gFremanLogErrorMsg.c_str();
  }
  return gFremanLogUnkownMsg.c_str();
}

////////////////////////////////////////////////
// Logger
////////////////////////////////////////////////

Logger::Logger()
{
}

Logger::~Logger()
{
}

////////////////////////////////////////////////
// message
////////////////////////////////////////////////

#define MAX_LOG_BUF 2048

bool Logger::message(LogLevel level, const char* format, ...)
{
  char msg[MAX_LOG_BUF], tsPrefix[MAX_LOG_BUF];

  time_t ts;
  struct tm* localts;
  ts = time(NULL);
  localts = localtime(&ts);

  strftime(tsPrefix, MAX_LOG_BUF, "%FT%T%z", localts);

  size_t prefixLen = snprintf(msg, MAX_LOG_BUF, "%s %s : ", tsPrefix, gForemanLoggerGetLevelString(level));

  va_list list;
  va_start(list, format);
  vsnprintf(msg + prefixLen, MAX_LOG_BUF - prefixLen, format, list);
  va_end(list);

  for (auto& outputter : *this) {
    outputter->output(level, msg);
  }

  return true;
}
