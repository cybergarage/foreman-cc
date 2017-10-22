/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno
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
// Memtric
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
// Query
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
// DataPoint
////////////////////////////////////////////////

typedef void ForemanMetricDataPoint;

time_t foreman_metric_datapoint_gettimestamp(ForemanMetricDataPoint* dp);
double foreman_metric_datapoint_getvalue(ForemanMetricDataPoint* dp);

////////////////////////////////////////////////
// DataPoints
////////////////////////////////////////////////

typedef void ForemanMetricDataPoints;

const char* foreman_metric_datapoints_getname(ForemanMetricDataPoints* dps);
size_t foreman_metric_datapoints_size(ForemanMetricDataPoints* dps);
ForemanMetricDataPoints* foreman_metric_datapoints_get(ForemanMetricDataPoints* dps, size_t n);

////////////////////////////////////////////////
// ResultSet
////////////////////////////////////////////////

typedef void ForemanMetricResultSet;

ForemanMetricResultSet* foreman_metric_resultset_new();

size_t foreman_metric_resultset_getdatapointcount(ForemanMetricResultSet* rs);

ForemanMetricDataPoints* foreman_metric_resultset_firstdatapoints(ForemanMetricResultSet* rs);
ForemanMetricDataPoints* foreman_metric_resultset_nextdatapoints(ForemanMetricResultSet* rs);
ForemanMetricDataPoints* foreman_metric_resultset_finddatapoints(ForemanMetricResultSet* rs, const char* name);

bool foreman_metric_resultset_delete(ForemanMetricResultSet* rs);

////////////////////////////////////////////////
// Store
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

bool foreman_metric_store_addmetric(ForemanMetricStore* store, ForemanMetric* m);
bool foreman_metric_store_query(ForemanMetricStore* store, ForemanMetricQuery* q, ForemanMetricResultSet* rs);

#ifdef __cplusplus
}
#endif

#endif
