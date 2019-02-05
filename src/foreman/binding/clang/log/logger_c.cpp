/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/log/Logger.h>
#include <foreman/log/logger-c.h>

using namespace Foreman::Log;

////////////////////////////////////////////////
// foreman_log_info
////////////////////////////////////////////////

bool foreman_log_info(const char* format, ...)
{
  va_list list;
  va_start(list, format);
  bool ret = Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::INFO, format, list);
  va_end(list);
  return ret;
}

////////////////////////////////////////////////
// foreman_log_info
////////////////////////////////////////////////

bool foreman_log_debug(const char* format, ...)
{
  va_list list;
  va_start(list, format);
  bool ret = Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::DBG, format, list);
  va_end(list);
  return ret;
}

////////////////////////////////////////////////
// foreman_log_error
////////////////////////////////////////////////

bool foreman_log_error(const char* format, ...)
{
  va_list list;
  va_start(list, format);
  bool ret = Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::ERROR, format, list);
  va_end(list);
  return ret;
}

////////////////////////////////////////////////
// foreman_log_warn
////////////////////////////////////////////////

bool foreman_log_warn(const char* format, ...)
{
  va_list list;
  va_start(list, format);
  bool ret = Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::WARN, format, list);
  va_end(list);
  return ret;
}

////////////////////////////////////////////////
// foreman_log_trace
////////////////////////////////////////////////

bool foreman_log_trace(const char* format, ...)
{
  va_list list;
  va_start(list, format);
  bool ret = Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::TRACE, format, list);
  va_end(list);
  return ret;
}
