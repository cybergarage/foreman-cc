/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_LOG_LEVEL_H_
#define _FOREMANCC_LOG_LEVEL_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <foreman/Const.h>

namespace Foreman {
namespace Log {

  enum LogLevel {
    ALL = FOREMANCC_LOGGER_LEVEL_ALL,
    DBG = FOREMANCC_LOGGER_LEVEL_DEBUG,
    TRACE = FOREMANCC_LOGGER_LEVEL_TRACE,
    INFO = FOREMANCC_LOGGER_LEVEL_INFO,
    WARN = FOREMANCC_LOGGER_LEVEL_WARN,
    ERROR = FOREMANCC_LOGGER_LEVEL_ERROR,
    FATAL = FOREMANCC_LOGGER_LEVEL_FATAL,
    NONE = FOREMANCC_LOGGER_LEVEL_NONE,
  };

}
}

#endif
