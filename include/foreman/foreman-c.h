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
  
ForemanMetric *foreman_metric_new();
bool foreman_metric_delete(ForemanMetric *m);

////////////////////////////////////////////////
// Store
////////////////////////////////////////////////

typedef void ForemanStore;

bool foreman_store_addmetric(ForemanStore *store, ForemanMetric *m);

#ifdef __cplusplus
}
#endif

#endif
