/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <foreman/util/Log.h>

static const char* log_error_s = LOG_LEVEL_ERROR_S;
static const char* log_warning_s = LOG_LEVEL_WARN_S;
static const char* log_info_s = LOG_LEVEL_INFO_S;
static const char* log_debug_s = LOG_LEVEL_DEBUG_S;

static const char* ForemanLogType2String(int type)
{
  switch (type) {
  case LOG_LEVEL_ERROR:
    return log_error_s;
    break;

  case LOG_LEVEL_WARN:
    return log_warning_s;
    break;

  case LOG_LEVEL_INFO:
    return log_info_s;
    break;

  case LOG_LEVEL_DEBUG:
    return log_debug_s;
    break;
  }

  return "";
}

void Foreman::Log::Output(int severity, const char* file, int line_n, const char* function, const char* format, ...)
{
  va_list list;

  char msg[MAX_LOG_BUF], tsPrefix[MAX_LOG_BUF];
  time_t ts;
  struct tm* localts;
  size_t prefixLen = -1;

  ts = time(NULL);
  localts = localtime(&ts);

  strftime(tsPrefix, MAX_LOG_BUF, "%c", localts);

  prefixLen = snprintf(msg, MAX_LOG_BUF, "%s [%s] ", tsPrefix, ForemanLogType2String(severity));

  va_start(list, format);
  vsnprintf(msg + prefixLen, MAX_LOG_BUF - prefixLen, format, list);
  va_end(list);

  printf("%s\n", msg);
}
