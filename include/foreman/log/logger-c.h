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

typedef void ForemanLogger;

ForemanLogger* foreman_logger_getsharedinstance();
void foreman_logger_setsharedinstance(ForemanLogger* logger);

ForemanLogger* foreman_logger_new();
bool foreman_logger_delete(ForemanLogger* logger);

bool foreman_logger_setlevel(ForemanLogger* logger, int level);
bool foreman_logger_setlevelstring(ForemanLogger* logger, const char* level);
bool foreman_logger_clear(ForemanLogger* logger);

bool foreman_logger_addstdoutputter(ForemanLogger* logger);
bool foreman_logger_addfileoutputter(ForemanLogger* logger, const char* filename);
bool foreman_logger_addnulloutputter(ForemanLogger* logger);

size_t foreman_logger_debug(ForemanLogger* obj, const char* msg);
size_t foreman_logger_trace(ForemanLogger* obj, const char* msg);
size_t foreman_logger_info(ForemanLogger* obj, const char* msg);
size_t foreman_logger_warn(ForemanLogger* obj, const char* msg);
size_t foreman_logger_error(ForemanLogger* obj, const char* msg);
size_t foreman_logger_fatal(ForemanLogger* obj, const char* msg);

#ifdef __cplusplus
}
#endif

#endif
