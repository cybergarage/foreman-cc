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

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////
// Parameter
////////////////////////////////////////////////

typedef void ForemanActionParameter;

ForemanActionParameter* foreman_action_parameter_new();
bool foreman_action_parameter_delete(ForemanActionParameter* param);

bool foreman_action_parameter_setname(ForemanActionParameter* param, const char* name);
bool foreman_action_parameter_getname(ForemanActionParameter* param, const char** name);

////////////////////////////////////////////////
// Parameters
////////////////////////////////////////////////

typedef void ForemanActionParameters;

ForemanActionParameters* foreman_action_parameters_new();
bool foreman_action_parameters_delete(ForemanActionParameters* params);

size_t foreman_action_parameters_size(ForemanActionParameters* params);

bool foreman_action_parameters_addparamerty(ForemanActionParameters* params, ForemanActionParameter* param);
ForemanActionParameter* foreman_action_parameters_getparamerty(ForemanActionParameters* params, size_t n);

////////////////////////////////////////////////
// ScriptManager
////////////////////////////////////////////////

typedef void ForemanActionScriptManager;

ForemanActionScriptManager* foreman_action_script_manager_new();
bool foreman_action_script_manager_excemethod(ForemanActionScriptManager* mgr, const char* name, ForemanActionParameters* params, ForemanActionParameters* results, ForemanError* err);
bool foreman_action_script_manager_delete(ForemanActionScriptManager* mgr);

#ifdef __cplusplus
}
#endif

#endif
