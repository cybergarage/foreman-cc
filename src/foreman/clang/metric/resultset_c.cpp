/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/foreman-c.h>
#include <foreman/metric/ResultSet.h>

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
  return ((ResultSet*)rs)->getDataPointCount();
}

////////////////////////////////////////////////
// foreman_metric_resultset_firstdatapoints
////////////////////////////////////////////////

ForemanMetricDataPoints* foreman_metric_resultset_firstdatapoints(ForemanMetricResultSet* rs)
{
  if (!rs)
    return NULL;

  return ((ResultSet*)rs)->firstDataPoint();
}

////////////////////////////////////////////////
// foreman_metric_resultset_nextdatapoints
////////////////////////////////////////////////

ForemanMetricDataPoints* foreman_metric_resultset_nextdatapoints(ForemanMetricResultSet* rs)
{
  if (!rs)
    return NULL;

  return ((ResultSet*)rs)->nextDataPoint();
}

////////////////////////////////////////////////
// foreman_metric_resultset_finddatapoints
////////////////////////////////////////////////

ForemanMetricDataPoints* foreman_metric_resultset_finddatapoints(ForemanMetricResultSet* rs, const char* name)
{
  if (!rs)
    return NULL;

  return ((ResultSet*)rs)->findDataPoints(name);
}
