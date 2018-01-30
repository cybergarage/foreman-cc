/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTER_C_H_
#define _FOREMANCC_REGISTER_C_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <foreman/common/common-c.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <time.h>

////////////////////////////////////////////////
// Object
////////////////////////////////////////////////

typedef void ForemanRegisterObject;

ForemanRegisterObject* foreman_register_object_new();
bool foreman_register_object_delete(ForemanRegisterObject* obj);

bool foreman_register_object_setkey(ForemanRegisterObject* obj, const char* name);
bool foreman_register_object_setdata(ForemanRegisterObject* obj, const char* data);

bool foreman_register_object_getkey(ForemanRegisterObject* obj, const char** name);
bool foreman_register_object_getdata(ForemanRegisterObject* obj, const char** data);

bool foreman_register_object_getversion(ForemanRegisterObject* obj, long *ver);
bool foreman_register_object_gettimestamp(ForemanRegisterObject* obj, time_t *ts);

////////////////////////////////////////////////
// Store
////////////////////////////////////////////////

typedef void ForemanRegisterStore;

ForemanRegisterStore* foreman_register_store_new();
bool foreman_register_store_delete(ForemanRegisterStore* store);

const char* foreman_register_store_gettype(ForemanRegisterStore* store);
const char* foreman_register_store_getversion(ForemanRegisterStore* store);

bool foreman_register_store_open(ForemanRegisterStore* store);
bool foreman_register_store_close(ForemanRegisterStore* store);
bool foreman_register_store_clear(ForemanRegisterStore* store);
size_t foreman_register_store_size(ForemanRegisterStore* store);

bool foreman_register_store_setobject(ForemanRegisterStore* store, ForemanRegisterObject* obj, ForemanError* err);
bool foreman_register_store_getobject(ForemanRegisterStore* store, const char* objId, ForemanRegisterObject* obj, ForemanError* err);
bool foreman_register_store_removeobject(ForemanRegisterStore* store, const char* objId, ForemanError* err);

#ifdef __cplusplus
}
#endif

#endif
