/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/foreman-c.h>
#include <foreman/metric/impl/StoreImpl.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// foreman_metric_store_matrix_create
////////////////////////////////////////////////

ForemanMetricStore* foreman_metric_store_matrix_create()
{
  return new MatrixStore();
}

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

#if defined(FOREMAN_ENABLE_BERINGEI)

ForemanMetricStore* foreman_metric_store_tsmap_create()
{
  return new BeringeiStore();
}

#endif
