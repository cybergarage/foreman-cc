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

bool foreman_log_info(const char* msg)
{
  return Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::INFO, msg);
}

////////////////////////////////////////////////
// foreman_log_info
////////////////////////////////////////////////

bool foreman_log_debug(const char* msg)
{
  return Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::DBG, msg);
}

////////////////////////////////////////////////
// foreman_log_error
////////////////////////////////////////////////

bool foreman_log_error(const char* msg)
{
  return Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::ERROR, msg);
}

////////////////////////////////////////////////
// foreman_log_warn
////////////////////////////////////////////////

bool foreman_log_warn(const char* msg)
{
  return Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::WARN, msg);
}

////////////////////////////////////////////////
// foreman_log_trace
////////////////////////////////////////////////

bool foreman_log_trace(const char* msg)
{
  return Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::TRACE, msg);
}
