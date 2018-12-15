/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_UTIL_LOG_H_
#define _FOREMANCC_UTIL_LOG_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define MAX_LOG_BUF 2048

#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_INFO 4
#define LOG_LEVEL_DEBUG 8

#define LOG_LEVEL_ERROR_S "ERROR"
#define LOG_LEVEL_WARN_S "WARN"
#define LOG_LEVEL_INFO_S "INFO"
#define LOG_LEVEL_DEBUG_S "DEBUG"

#define LOG_ALL (LOG_ERROR | LOG_WARNING | LOG_INFO | LOG_DEBUG)

namespace Foreman {
namespace Log {

  void Output(int severity, const char* file, int line_n, const char* function, const char* format, ...);

}
}

#if defined(DEBUG)

#if defined(__USE_ISOC99)
#define LOG_ERROR(format, ...) Foreman::Log::Output(LOG_LEVEL_ERROR, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, __VA_ARGS__)
#define LOG_WARN(format, ...) Foreman::Log::Output(LOG_LEVEL_WARN, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, __VA_ARGS__)
#define LOG_INFO(format, ...) Foreman::Log::Output(LOG_LEVEL_INFO, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, __VA_ARGS__)
#define LOG_DEBUG(format, ...) Foreman::Log::Output(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, __VA_ARGS__)
#else
#define LOG_ERROR(format...) Foreman::Log::Output(LOG_LEVEL_ERROR, __FILE__, __LINE__, __PRETTY_FUNCTION__, format)
#define LOG_WARN(format...) Foreman::Log::Output(LOG_LEVEL_WARN, __FILE__, __LINE__, __PRETTY_FUNCTION__, format)
#define LOG_INFO(format...) Foreman::Log::Output(LOG_LEVEL_INFO, __FILE__, __LINE__, __PRETTY_FUNCTION__, format)
#define LOG_DEBUG(format...) Foreman::Log::Output(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __PRETTY_FUNCTION__, format)
#endif

#else

#if defined(__USE_ISOC99)
#define LOG_ERROR(format, ...)
#define LOG_WARN(format, ...)
#define LOG_INFO(format, ...)
#define LOG_DEBUG(format, ...)
#else
#define LOG_ERROR(format...)
#define LOG_WARN(format...)
#define LOG_INFO(format...)
#define LOG_DEBUG(format...)
#endif

#endif

#endif /* _FOREMANCC_UTIL_LOG_H_ */
