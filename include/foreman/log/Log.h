/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_LOG_LOG_H_
#define _FOREMANCC_LOG_LOG_H_

#include <foreman/log/Logger.h>

#if defined(__USE_ISOC99)
#if defined(DEBUG)
#define FOREMAN_LOG_DEBUG(format, ...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::DEBUG, format, __VA_ARGS__)
#else
#define FOREMAN_LOG_DEBUG(format, ...)
#endif
#define FOREMAN_LOG_TRACE(format, ...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::TRACE, format, __VA_ARGS__)
#define FOREMAN_LOG_INFO(format, ...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::INFO, format, __VA_ARGS__)
#define FOREMAN_LOG_WARN(format, ...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::WARN, format, __VA_ARGS__)
#define FOREMAN_LOG_ERROR(format, ...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::ERROR, format, __VA_ARGS__)
#define FOREMAN_LOG_FATAL(format, ...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::FATAL, format, __VA_ARGS__)
#else
#if defined(DEBUG)
#define FOREMAN_LOG_DEBUG(format...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::DEBUG, format, __VA_ARGS__)
#else
#define FOREMAN_LOG_DEBUG(format...)
#endif
#define FOREMAN_LOG_TRACE(format...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::TRACE, format, __VA_ARGS__)
#define FOREMAN_LOG_INFO(format...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::INFO, format, __VA_ARGS__)
#define FOREMAN_LOG_WARN(format...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::WARN, format, __VA_ARGS__)
#define FOREMAN_LOG_ERROR(format...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::ERROR, format, __VA_ARGS__)
#define FOREMAN_LOG_FATAL(format...) Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::FATAL, format, __VA_ARGS__)
#endif

#endif
