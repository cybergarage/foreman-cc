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
// foreman_logger_setsharedinstance
////////////////////////////////////////////////

void foreman_logger_setsharedinstance(ForemanLogger* logger)
{
  Logger::SetSharedInstance((Logger*)logger);
}

////////////////////////////////////////////////
// foreman_logger_getsharedinstance
////////////////////////////////////////////////

ForemanLogger* foreman_logger_getsharedinstance()
{
  return Logger::GetSharedInstance();
}

////////////////////////////////////////////////
// foreman_logger_new
////////////////////////////////////////////////

ForemanLogger* foreman_logger_new()
{
  return new Logger();
}

////////////////////////////////////////////////
// foreman_logger_delete
////////////////////////////////////////////////

bool foreman_logger_delete(ForemanLogger* logger)
{
  if (!logger)
    return false;
  delete (Logger*)logger;
  return true;
}

////////////////////////////////////////////////
// foreman_logger_setlevel
////////////////////////////////////////////////

bool foreman_logger_setlevel(ForemanLogger* logger, int level)
{
  if (!logger)
    return false;

  ((Logger*)logger)->setLevel(LogLevel(level));

  return true;
}

////////////////////////////////////////////////
// foreman_logger_setlevelstring
////////////////////////////////////////////////

bool foreman_logger_setlevelstring(ForemanLogger* logger, const char* level)
{
  if (!logger)
    return false;

  return ((Logger*)logger)->setLevelString(level);
}

////////////////////////////////////////////////
// foreman_logger_addstdoutputter
////////////////////////////////////////////////

bool foreman_logger_addstdoutputter(ForemanLogger* logger)
{
  if (!logger)
    return false;

  ((Logger*)logger)->addOutputter(new StdoutOutputter());

  return true;
}

////////////////////////////////////////////////
// foreman_logger_addfileoutputter
////////////////////////////////////////////////

bool foreman_logger_addfileoutputter(ForemanLogger* logger, const char* filename)
{
  if (!logger)
    return false;

  ((Logger*)logger)->addOutputter(new FileOutputter(filename));

  return true;
}

////////////////////////////////////////////////
// foreman_logger_addnulloutputter
////////////////////////////////////////////////

bool foreman_logger_addnulloutputter(ForemanLogger* logger)
{
  if (!logger)
    return false;

  ((Logger*)logger)->addOutputter(new NullOutputter);

  return true;
}

////////////////////////////////////////////////
// foreman_logger_clear
////////////////////////////////////////////////

bool foreman_logger_clear(ForemanLogger* logger)
{
  if (!logger)
    return false;

  ((Logger*)logger)->clear();

  return true;
}

////////////////////////////////////////////////
// foreman_logger_info
////////////////////////////////////////////////

size_t foreman_logger_info(ForemanLogger* logger, const char* format, ...)
{
  if (!logger)
    return 0;

  va_list list;
  va_start(list, format);
  size_t n = ((Logger*)logger)->info(format, list);
  va_end(list);
  return n;
}

////////////////////////////////////////////////
// foreman_logger_debug
////////////////////////////////////////////////

size_t foreman_logger_debug(ForemanLogger* logger, const char* format, ...)
{
  if (!logger)
    return 0;

  va_list list;
  va_start(list, format);
  size_t n = ((Logger*)logger)->debug(format, list);
  va_end(list);
  return n;
}

////////////////////////////////////////////////
// foreman_logger_trace
////////////////////////////////////////////////

size_t foreman_logger_trace(ForemanLogger* logger, const char* format, ...)
{
  if (!logger)
    return 0;

  va_list list;
  va_start(list, format);
  size_t n = ((Logger*)logger)->trace(format, list);
  va_end(list);
  return n;
}

////////////////////////////////////////////////
// foreman_logger_warn
////////////////////////////////////////////////

size_t foreman_logger_warn(ForemanLogger* logger, const char* format, ...)
{
  if (!logger)
    return 0;

  va_list list;
  va_start(list, format);
  size_t n = ((Logger*)logger)->warn(format, list);
  va_end(list);
  return n;
}

////////////////////////////////////////////////
// foreman_logger_error
////////////////////////////////////////////////

size_t foreman_logger_error(ForemanLogger* logger, const char* format, ...)
{
  if (!logger)
    return 0;

  va_list list;
  va_start(list, format);
  size_t n = ((Logger*)logger)->error(format, list);
  va_end(list);
  return n;
}

////////////////////////////////////////////////
// foreman_logger_fatal
////////////////////////////////////////////////

size_t foreman_logger_fatal(ForemanLogger* logger, const char* format, ...)
{
  if (!logger)
    return 0;

  va_list list;
  va_start(list, format);
  size_t n = ((Logger*)logger)->fatal(format, list);
  va_end(list);
  return n;
}
