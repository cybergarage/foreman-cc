/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_FOREMANC_H_
#define _FOREMANCC_FOREMANC_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <time.h>

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
  
bool foreman_error_getmessage(ForemanError* e, const char** msg);
bool foreman_error_getcode(ForemanError* e, int* code);
bool foreman_error_getdetailmessage(ForemanError* e, const char** msg);
bool foreman_error_getdetailcode(ForemanError* e, int* code);
bool foreman_error_getlineno(ForemanError* e, int *lineno);
bool foreman_error_getfilename(ForemanError* e, const char** name);
bool foreman_error_getfuncname(ForemanError* e, const char** name);

bool foreman_error_delete(ForemanError* e);

////////////////////////////////////////////////
// Registry::Property
////////////////////////////////////////////////

typedef void ForemanRegistryProperty;

ForemanRegistryProperty* foreman_registry_property_new();
bool foreman_registry_property_delete(ForemanRegistryProperty* prop);

bool foreman_registry_property_setname(ForemanRegistryProperty* prop, const char* name);
bool foreman_registry_property_setdata(ForemanRegistryProperty* prop, const char* data);

bool foreman_registry_property_getname(ForemanRegistryProperty* prop, const char** name);
bool foreman_registry_property_getdata(ForemanRegistryProperty* prop, const char** data);

////////////////////////////////////////////////
// Registry::Properties
////////////////////////////////////////////////

typedef void ForemanRegistryProperties;

ForemanRegistryProperties* foreman_registry_properties_new();
bool foreman_registry_properties_delete(ForemanRegistryProperties* props);

size_t foreman_registry_properties_size(ForemanRegistryProperties* props);

bool foreman_registry_properties_addproperty(ForemanRegistryProperties* props, ForemanRegistryProperty* prop);
ForemanRegistryProperty* foreman_registry_properties_getproperty(ForemanRegistryProperties* props, size_t n);

////////////////////////////////////////////////
// Registry::Object
////////////////////////////////////////////////

typedef void ForemanRegistryObject;

ForemanRegistryObject* foreman_registry_object_new();
bool foreman_registry_object_delete(ForemanRegistryObject* obj);

bool foreman_registry_object_setid(ForemanRegistryObject* obj, const char* id);
bool foreman_registry_object_setparentid(ForemanRegistryObject* obj, const char* pid);
bool foreman_registry_object_setname(ForemanRegistryObject* obj, const char* name);
bool foreman_registry_object_setdata(ForemanRegistryObject* obj, const char* pid);

bool foreman_registry_object_getid(ForemanRegistryObject* obj, const char** id);
bool foreman_registry_object_getparentid(ForemanRegistryObject* obj, const char** pid);
bool foreman_registry_object_getname(ForemanRegistryObject* obj, const char** name);
bool foreman_registry_object_getdata(ForemanRegistryObject* obj, const char** data);

////////////////////////////////////////////////
// Registry::Objects
////////////////////////////////////////////////

typedef void ForemanRegistryObjects;

ForemanRegistryObjects* foreman_registry_objects_new();
bool foreman_registry_objects_delete(ForemanRegistryObjects* objs);

size_t foreman_registry_objects_size(ForemanRegistryObjects* objs);

bool foreman_registry_objects_addobject(ForemanRegistryObjects* objs, ForemanRegistryObject* obj);
ForemanRegistryObject* foreman_registry_objects_getobject(ForemanRegistryObjects* objs, size_t n);

////////////////////////////////////////////////
// Registry::Query
////////////////////////////////////////////////

typedef void ForemanRegistryQuery;

ForemanRegistryQuery* foreman_registry_query_new();
bool foreman_registry_query_delete(ForemanRegistryQuery* q);

bool foreman_registry_query_setparentid(ForemanRegistryQuery* q, const char* pid);
bool foreman_registry_query_getparentid(ForemanRegistryQuery* q, const char** pid);

////////////////////////////////////////////////
// Registry::Store
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

////////////////////////////////////////////////
// Metric::Metric
////////////////////////////////////////////////

typedef void ForemanMetric;

ForemanMetric* foreman_metric_new();

bool foreman_metric_setname(ForemanMetric* m, const char* name);
bool foreman_metric_setvalue(ForemanMetric* m, double value);
bool foreman_metric_settimestamp(ForemanMetric* m, time_t ts);

bool foreman_metric_getname(ForemanMetric* m, const char** name);
bool foreman_metric_getvalue(ForemanMetric* m, double* value);
bool foreman_metric_gettimestamp(ForemanMetric* m, time_t* ts);

bool foreman_metric_delete(ForemanMetric* m);

////////////////////////////////////////////////
// Metric::Query
////////////////////////////////////////////////

typedef void ForemanMetricQuery;

ForemanMetricQuery* foreman_metric_query_new();

bool foreman_metric_query_settarget(ForemanMetricQuery* q, const char* name);
bool foreman_metric_query_setfrom(ForemanMetricQuery* q, time_t ts);
bool foreman_metric_query_setuntil(ForemanMetricQuery* q, time_t ts);
bool foreman_metric_query_setinterval(ForemanMetricQuery* q, time_t ts);

bool foreman_metric_query_gettarget(ForemanMetricQuery* q, const char** name);
bool foreman_metric_query_getfrom(ForemanMetricQuery* q, time_t* ts);
bool foreman_metric_query_getuntil(ForemanMetricQuery* q, time_t* ts);
bool foreman_metric_query_getinterval(ForemanMetricQuery* q, time_t* ts);

bool foreman_metric_query_delete(ForemanMetricQuery* q);

////////////////////////////////////////////////
// Metric::DataPoint
////////////////////////////////////////////////

typedef void ForemanMetricDataPoint;

time_t foreman_metric_datapoint_gettimestamp(ForemanMetricDataPoint* dp);
double foreman_metric_datapoint_getvalue(ForemanMetricDataPoint* dp);

////////////////////////////////////////////////
// Metric::DataPoints
////////////////////////////////////////////////

typedef void ForemanMetricDataPoints;

const char* foreman_metric_datapoints_getname(ForemanMetricDataPoints* dps);
size_t foreman_metric_datapoints_size(ForemanMetricDataPoints* dps);
ForemanMetricDataPoints* foreman_metric_datapoints_get(ForemanMetricDataPoints* dps, size_t n);

////////////////////////////////////////////////
// Metric::ResultSet
////////////////////////////////////////////////

typedef void ForemanMetricResultSet;

ForemanMetricResultSet* foreman_metric_resultset_new();

size_t foreman_metric_resultset_getdatapointcount(ForemanMetricResultSet* rs);

ForemanMetricDataPoints* foreman_metric_resultset_firstdatapoints(ForemanMetricResultSet* rs);
ForemanMetricDataPoints* foreman_metric_resultset_nextdatapoints(ForemanMetricResultSet* rs);
ForemanMetricDataPoints* foreman_metric_resultset_finddatapoints(ForemanMetricResultSet* rs, const char* name);

bool foreman_metric_resultset_delete(ForemanMetricResultSet* rs);

////////////////////////////////////////////////
// Metric::Store
////////////////////////////////////////////////

typedef void ForemanMetricStore;

ForemanMetricStore* foreman_metric_store_matrix_create();
ForemanMetricStore* foreman_metric_store_ringmap_create();
ForemanMetricStore* foreman_metric_store_sqlite_create();

#if defined(FOREMAN_ENABLE_BERINGEI)
ForemanMetricStore* foreman_metric_store_tsmap_create();
#endif

bool foreman_metric_store_delete(ForemanMetricStore* store);

bool foreman_metric_store_setretentioninterval(ForemanMetricStore* store, time_t value);
time_t foreman_metric_store_getretentioninterval(ForemanMetricStore* store);

bool foreman_metric_store_open(ForemanMetricStore* store);
bool foreman_metric_store_close(ForemanMetricStore* store);
bool foreman_metric_store_clear(ForemanMetricStore* store);

bool foreman_metric_store_addmetric(ForemanMetricStore* store, ForemanMetric* m);
bool foreman_metric_store_query(ForemanMetricStore* store, ForemanMetricQuery* q, ForemanMetricResultSet* rs);

#ifdef __cplusplus
}
#endif

#endif
