/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/ResultSet.h>
#include <foreman/metric/metric-c.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// foreman_metric_resultset_new
////////////////////////////////////////////////

ForemanMetricResultSet* foreman_metric_resultset_new()
{
  return new ResultSet();
}

////////////////////////////////////////////////
// foreman_metric_resultset_delete
////////////////////////////////////////////////

bool foreman_metric_resultset_delete(ForemanMetricResultSet* rs)
{
  if (!rs)
    return false;
  delete (ResultSet*)rs;
  return true;
}

////////////////////////////////////////////////
// foreman_metric_resultset_getdatapointcount
////////////////////////////////////////////////

size_t foreman_metric_resultset_getdatapointcount(ForemanMetricResultSet* rs)
{
  if (!rs)
    return 0;
  return ((ResultSet*)rs)->getMetricsCount();
}

////////////////////////////////////////////////
// foreman_metric_resultset_getfirstmetrics
////////////////////////////////////////////////

ForemanMetrics* foreman_metric_resultset_getfirstmetrics(ForemanMetricResultSet* rs)
{
  if (!rs)
    return NULL;

  return ((ResultSet*)rs)->firstMetrics();
}

////////////////////////////////////////////////
// foreman_metric_resultset_getnextmetrics
////////////////////////////////////////////////

ForemanMetrics* foreman_metric_resultset_getnextmetrics(ForemanMetricResultSet* rs)
{
  if (!rs)
    return NULL;

  return ((ResultSet*)rs)->nextMetrics();
}

////////////////////////////////////////////////
// foreman_metric_resultset_findmetrics
////////////////////////////////////////////////

ForemanMetrics* foreman_metric_resultset_findmetrics(ForemanMetricResultSet* rs, const char* name)
{
  if (!rs)
    return NULL;

  return ((ResultSet*)rs)->findMetrics(name);
}
