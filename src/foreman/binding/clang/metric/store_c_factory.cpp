/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/impl/StoreImpl.h>
#include <foreman/metric/metric-c.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// foreman_metric_store_ringmap_create
////////////////////////////////////////////////

ForemanMetricStore* foreman_metric_store_ringmap_create()
{
  return new RingMapStore();
}

////////////////////////////////////////////////
// foreman_metric_store_sqlite_create
////////////////////////////////////////////////

ForemanMetricStore* foreman_metric_store_sqlite_create()
{
  return new NarrowTableStore();
}

////////////////////////////////////////////////
// foreman_metric_store_tsmap_create
////////////////////////////////////////////////

ForemanMetricStore* foreman_metric_store_tsmap_create()
{
#if defined(FOREMAN_ENABLE_BERINGEI)
  return new BeringeiStore();
#else
  return NULL;
#endif
}
