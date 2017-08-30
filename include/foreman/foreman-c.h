/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_FOREMANC_H_
#define _FOREMANCC_FOREMANC_H_

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

typedef void ForemanQuery;

ForemanQuery* foreman_query_new();

bool foreman_query_settarget(ForemanQuery* q, const char* name);
bool foreman_query_setfrom(ForemanQuery* q, time_t ts);
bool foreman_query_setuntil(ForemanQuery* q, time_t ts);
bool foreman_query_setinterval(ForemanQuery* q, time_t ts);

bool foreman_query_gettarget(ForemanQuery* q, const char** name);
bool foreman_query_getfrom(ForemanQuery* q, time_t* ts);
bool foreman_query_getuntil(ForemanQuery* q, time_t* ts);
bool foreman_query_getinterval(ForemanQuery* q, time_t* ts);

bool foreman_query_delete(ForemanQuery* q);

////////////////////////////////////////////////
// ResultSet
////////////////////////////////////////////////

typedef void ForemanResultSet;

ForemanResultSet* foreman_resultset_new();

size_t foreman_resultset_getcount(ForemanResultSet* rs);

bool foreman_resultset_getvalue(ForemanResultSet* rs, size_t n, double* value);
double* foreman_resultset_getvalues(ForemanResultSet* rs);

bool foreman_resultset_delete(ForemanResultSet* rs);

////////////////////////////////////////////////
// Store
////////////////////////////////////////////////

typedef void ForemanStore;

ForemanStore* foreman_store_matrix_create();
ForemanStore* foreman_store_ringmap_create();
ForemanStore* foreman_store_sqlite_create();
ForemanStore* foreman_store_tsmap_create();

bool foreman_store_delete(ForemanStore* store);

bool foreman_store_open(ForemanStore* store);
bool foreman_store_close(ForemanStore* store);

bool foreman_store_addmetric(ForemanStore* store, ForemanMetric* m);
bool foreman_store_query(ForemanStore* store, ForemanQuery* q, ForemanResultSet* rs);

#ifdef __cplusplus
}
#endif

#endif
