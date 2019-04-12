/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_COMMON_C_H_
#define _FOREMANCC_COMMON_C_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

////////////////////////////////////////////////
// Byte
////////////////////////////////////////////////

#if !defined(byte)
typedef unsigned char byte;
#endif

////////////////////////////////////////////////
// Error
////////////////////////////////////////////////

typedef void ForemanError;

ForemanError* foreman_error_new();

bool foreman_error_setmessage(ForemanError* e, const char* msg);
bool foreman_error_setcode(ForemanError* e, int code);
bool foreman_error_setdetailmessage(ForemanError* e, const char* msg);
bool foreman_error_setdetailcode(ForemanError* e, int code);
bool foreman_error_setlineno(ForemanError* e, int lineno);
bool foreman_error_setfilename(ForemanError* e, const char* name);
bool foreman_error_setfuncname(ForemanError* e, const char* name);

bool foreman_error_hasmessage(ForemanError* e);
bool foreman_error_hascode(ForemanError* e);
bool foreman_error_hasdetailmessage(ForemanError* e);
bool foreman_error_hasdetailcode(ForemanError* e);

bool foreman_error_getmessage(ForemanError* e, const char** msg);
bool foreman_error_getcode(ForemanError* e, int* code);
bool foreman_error_getdetailmessage(ForemanError* e, const char** msg);
bool foreman_error_getdetailcode(ForemanError* e, int* code);
bool foreman_error_getlineno(ForemanError* e, int* lineno);
bool foreman_error_getfilename(ForemanError* e, const char** name);
bool foreman_error_getfuncname(ForemanError* e, const char** name);

bool foreman_error_isinternalerror(ForemanError* e);

bool foreman_error_delete(ForemanError* e);

#ifdef __cplusplus
}
#endif

#endif
