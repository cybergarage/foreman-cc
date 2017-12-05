/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTRY_C_H_
#define _FOREMANCC_REGISTRY_C_H_

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
// Property
////////////////////////////////////////////////

typedef void ForemanRegistryProperty;

ForemanRegistryProperty* foreman_registry_property_new();
bool foreman_registry_property_delete(ForemanRegistryProperty* prop);

bool foreman_registry_property_setname(ForemanRegistryProperty* prop, const char* name);
bool foreman_registry_property_setdata(ForemanRegistryProperty* prop, const char* data);

bool foreman_registry_property_getname(ForemanRegistryProperty* prop, const char** name);
bool foreman_registry_property_getdata(ForemanRegistryProperty* prop, const char** data);

////////////////////////////////////////////////
// Properties
////////////////////////////////////////////////

typedef void ForemanRegistryProperties;

ForemanRegistryProperties* foreman_registry_properties_new();
bool foreman_registry_properties_delete(ForemanRegistryProperties* props);

size_t foreman_registry_properties_size(ForemanRegistryProperties* props);

bool foreman_registry_properties_addproperty(ForemanRegistryProperties* props, ForemanRegistryProperty* prop);
ForemanRegistryProperty* foreman_registry_properties_getproperty(ForemanRegistryProperties* props, size_t n);

////////////////////////////////////////////////
// Object
////////////////////////////////////////////////

typedef void ForemanRegistryObject;

ForemanRegistryObject* foreman_registry_object_new();
bool foreman_registry_object_delete(ForemanRegistryObject* obj);

bool foreman_registry_object_setid(ForemanRegistryObject* obj, const char* id);
bool foreman_registry_object_setparentid(ForemanRegistryObject* obj, const char* pid);
bool foreman_registry_object_setname(ForemanRegistryObject* obj, const char* name);
bool foreman_registry_object_setdata(ForemanRegistryObject* obj, const char* data);
bool foreman_registry_object_setpropertydata(ForemanRegistryObject* obj, const char* data);
bool foreman_registry_object_setproperty(ForemanRegistryObject* obj, ForemanRegistryProperty* prop);

bool foreman_registry_object_getid(ForemanRegistryObject* obj, const char** id);
bool foreman_registry_object_getparentid(ForemanRegistryObject* obj, const char** pid);
bool foreman_registry_object_getname(ForemanRegistryObject* obj, const char** name);
bool foreman_registry_object_getdata(ForemanRegistryObject* obj, const char** data);
bool foreman_registry_object_getpropertydata(ForemanRegistryObject* obj, const char** data);
bool foreman_registry_object_getproperties(ForemanRegistryObject* obj, ForemanRegistryProperties* props);

////////////////////////////////////////////////
// Objects
////////////////////////////////////////////////

typedef void ForemanRegistryObjects;

ForemanRegistryObjects* foreman_registry_objects_new();
bool foreman_registry_objects_delete(ForemanRegistryObjects* objs);

size_t foreman_registry_objects_size(ForemanRegistryObjects* objs);

bool foreman_registry_objects_addobject(ForemanRegistryObjects* objs, ForemanRegistryObject* obj);
ForemanRegistryObject* foreman_registry_objects_getobject(ForemanRegistryObjects* objs, size_t n);

////////////////////////////////////////////////
// Query
////////////////////////////////////////////////

typedef void ForemanRegistryQuery;

ForemanRegistryQuery* foreman_registry_query_new();
bool foreman_registry_query_delete(ForemanRegistryQuery* q);

bool foreman_registry_query_setparentid(ForemanRegistryQuery* q, const char* pid);
bool foreman_registry_query_getparentid(ForemanRegistryQuery* q, const char** pid);

////////////////////////////////////////////////
// Store
////////////////////////////////////////////////

typedef void ForemanRegistryStore;

ForemanRegistryStore* foreman_registry_sqlite_store_new();
bool foreman_registry_store_delete(ForemanRegistryStore* store);

const char* foreman_registry_store_gettype(ForemanRegistryStore* store);
const char* foreman_registry_store_getversion(ForemanRegistryStore* store);

bool foreman_registry_store_open(ForemanRegistryStore* store);
bool foreman_registry_store_close(ForemanRegistryStore* store);
bool foreman_registry_store_clear(ForemanRegistryStore* store);

bool foreman_registry_store_createobject(ForemanRegistryStore* store, ForemanRegistryObject* obj, ForemanError* err);
bool foreman_registry_store_updateobject(ForemanRegistryStore* store, ForemanRegistryObject* obj, ForemanError* err);
bool foreman_registry_store_getobject(ForemanRegistryStore* store, const char* objId, ForemanRegistryObject* obj, ForemanError* err);
bool foreman_registry_store_deleteobject(ForemanRegistryStore* store, const char* objId, ForemanError* err);

bool foreman_registry_store_browse(ForemanRegistryStore* store, ForemanRegistryQuery* q, ForemanRegistryObjects* objs, ForemanError* err);
bool foreman_registry_store_search(ForemanRegistryStore* store, ForemanRegistryQuery* q, ForemanRegistryObjects* objs, ForemanError* err);

#ifdef __cplusplus
}
#endif

#endif
