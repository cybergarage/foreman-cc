/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_C_H_
#define _FOREMANCC_METRIC_C_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <foreman/common/common-c.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////
// Metric
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
// Metrics
////////////////////////////////////////////////

typedef void ForemanMetrics;

const char* foreman_metric_metrics_getname(ForemanMetrics* m);
size_t foreman_metric_metrics_getdatapointsize(ForemanMetrics* m);
ForemanMetrics* foreman_metric_metrics_getdatapoint(ForemanMetrics* m, size_t n);

////////////////////////////////////////////////
// ResultSet
////////////////////////////////////////////////

typedef void ForemanMetricResultSet;

ForemanMetricResultSet* foreman_metric_resultset_new();

size_t foreman_metric_resultset_getdatapointcount(ForemanMetricResultSet* rs);

ForemanMetrics* foreman_metric_resultset_getfirstmetrics(ForemanMetricResultSet* rs);
ForemanMetrics* foreman_metric_resultset_getnextmetrics(ForemanMetricResultSet* rs);
ForemanMetrics* foreman_metric_resultset_findmetrics(ForemanMetricResultSet* rs, const char* name);

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
bool foreman_metric_store_clear(ForemanMetricStore* store);

bool foreman_metric_store_addmetric(ForemanMetricStore* store, ForemanMetric* m);
bool foreman_metric_store_querymetric(ForemanMetricStore* store, ForemanMetricQuery* q, ForemanMetricResultSet* rs);
bool foreman_metric_store_querydata(ForemanMetricStore* store, ForemanMetricQuery* q, ForemanMetricResultSet* rs);
bool foreman_metric_store_analyzedata(ForemanMetricStore* store, ForemanMetricQuery* q, ForemanMetricResultSet* rs);

#ifdef __cplusplus
}
#endif

#endif
