/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ACTION_C_H_
#define _FOREMANCC_ACTION_C_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <foreman/common/common-c.h>
#include <foreman/metric/metric-c.h>
#include <foreman/register/register-c.h>
#include <foreman/registry/registry-c.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////
// Method
////////////////////////////////////////////////

typedef void ForemanActionMethod;

ForemanActionMethod* foreman_action_method_new(const char* language);

bool foreman_action_method_delete(ForemanActionMethod* method);

bool foreman_action_method_setname(ForemanActionMethod* method, const char* name);
bool foreman_action_method_getname(ForemanActionMethod* method, const char** name);

bool foreman_action_method_setlanguage(ForemanActionMethod* method, const char* lang);
bool foreman_action_method_getlanguage(ForemanActionMethod* method, const char** lang);

bool foreman_action_method_setcode(ForemanActionMethod* method, const byte* code, size_t codeLen);
bool foreman_action_method_setstringcode(ForemanActionMethod* method, const char* code);
bool foreman_action_method_getcode(ForemanActionMethod* method, const byte** code);
bool foreman_action_method_getcodelength(ForemanActionMethod* method, size_t* size);
bool foreman_action_method_getstringcode(ForemanActionMethod* method, const char** code);

////////////////////////////////////////////////
// Parameter
////////////////////////////////////////////////

typedef void ForemanActionParameter;

ForemanActionParameter* foreman_action_parameter_integer_new();
ForemanActionParameter* foreman_action_parameter_real_new();
ForemanActionParameter* foreman_action_parameter_bool_new();
ForemanActionParameter* foreman_action_parameter_string_new();

bool foreman_action_parameter_delete(ForemanActionParameter* param);

bool foreman_action_parameter_setname(ForemanActionParameter* param, const char* name);
const char* foreman_action_parameter_getname(ForemanActionParameter* param);

bool foreman_action_parameter_isinteger(ForemanActionParameter* param);
bool foreman_action_parameter_isreal(ForemanActionParameter* param);
bool foreman_action_parameter_isbool(ForemanActionParameter* param);
bool foreman_action_parameter_isstring(ForemanActionParameter* param);

bool foreman_action_parameter_setinteger(ForemanActionParameter* param, long value);
bool foreman_action_parameter_setreal(ForemanActionParameter* param, double value);
bool foreman_action_parameter_setbool(ForemanActionParameter* param, bool value);
bool foreman_action_parameter_setstring(ForemanActionParameter* param, const char* value);

long foreman_action_parameter_getinteger(ForemanActionParameter* param);
double foreman_action_parameter_getreal(ForemanActionParameter* param);
bool foreman_action_parameter_getbool(ForemanActionParameter* param);
const char* foreman_action_parameter_getstring(ForemanActionParameter* param);

////////////////////////////////////////////////
// Parameters
////////////////////////////////////////////////

typedef void ForemanActionParameters;

ForemanActionParameters* foreman_action_parameters_new();
bool foreman_action_parameters_delete(ForemanActionParameters* params);

size_t foreman_action_parameters_size(ForemanActionParameters* params);

bool foreman_action_parameters_addparameter(ForemanActionParameters* params, ForemanActionParameter* param);
ForemanActionParameter* foreman_action_parameters_getparameter(ForemanActionParameters* params, size_t n);

////////////////////////////////////////////////
// Manager
////////////////////////////////////////////////

typedef void ForemanActionManager;

ForemanActionManager* foreman_action_manager_new();
bool foreman_action_manager_delete(ForemanActionManager* mgr);

bool foreman_action_manager_setregisterstore(ForemanActionManager* mgr, ForemanRegisterStore* store);
bool foreman_action_manager_setregistrystore(ForemanActionManager* mgr, ForemanRegistryStore* store);
bool foreman_action_manager_setmetricstore(ForemanActionManager* mgr, ForemanMetricStore* store);

bool foreman_action_manager_hasengine(ForemanActionManager* mgr, const char* name);

bool foreman_action_manager_addmethod(ForemanActionManager* mgr, ForemanActionMethod* method, ForemanError* err);
bool foreman_action_manager_removemethod(ForemanActionManager* mgr, const char* name, ForemanError* err);
bool foreman_action_manager_hasmethod(ForemanActionManager* mgr, const char* name);
bool foreman_action_manager_execmethod(ForemanActionManager* mgr, const char* name, ForemanActionParameters* params, ForemanActionParameters* results, ForemanError* err);
bool foreman_action_manager_removeallmethods(ForemanActionManager* mgr, ForemanError* err);

ForemanActionMethod* foreman_action_manager_getmethod(ForemanActionManager* mgr, const char* name);
ForemanActionMethod* foreman_action_manager_getfirstmethod(ForemanActionManager* mgr);
ForemanActionMethod* foreman_action_manager_nextmethod(ForemanActionManager* mgr, ForemanActionMethod* method);

#ifdef __cplusplus
}
#endif

#endif
