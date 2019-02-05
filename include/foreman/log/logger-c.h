/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_LOGGER_C_H_
#define _FOREMANCC_LOGGER_C_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <foreman/common/common-c.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

bool foreman_log_info(const char* format, ...);
bool foreman_log_debug(const char* format, ...);
bool foreman_log_error(const char* format, ...);
bool foreman_log_warn(const char* format, ...);
bool foreman_log_trace(const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif
