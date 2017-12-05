/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/metric-c.h>
#include <foreman/metric/Query.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// foreman_metric_query_new
////////////////////////////////////////////////

ForemanMetricQuery* foreman_metric_query_new()
{
  return new Query();
}

////////////////////////////////////////////////
// foreman_metric_query_delete
////////////////////////////////////////////////

bool foreman_metric_query_delete(ForemanMetricQuery* q)
{
  if (!q)
    return false;
  delete (Query*)q;
  return true;
}

////////////////////////////////////////////////
// foreman_metric_query_settarget
////////////////////////////////////////////////

bool foreman_metric_query_settarget(ForemanMetricQuery* q, const char* name)
{
  if (!q || !name)
    return false;
  ((Query*)q)->target = name;
  return true;
}

////////////////////////////////////////////////
// foreman_metric_query_gettarget
////////////////////////////////////////////////

bool foreman_metric_query_gettarget(ForemanMetricQuery* q, const char** name)
{
  if (!q || !name)
    return false;
  *name = ((Query*)q)->target.c_str();
  return true;
}

////////////////////////////////////////////////
// foreman_metric_query_setfrom
////////////////////////////////////////////////

bool foreman_metric_query_setfrom(ForemanMetricQuery* q, time_t ts)
{
  if (!q)
    return false;
  ((Query*)q)->from = ts;
  return true;
}

////////////////////////////////////////////////
// foreman_metric_query_getfrom
////////////////////////////////////////////////

bool foreman_metric_query_getfrom(ForemanMetricQuery* q, time_t* ts)
{
  if (!q)
    return false;
  *ts = ((Query*)q)->from;
  return true;
}

////////////////////////////////////////////////
// foreman_metric_query_setuntil
////////////////////////////////////////////////

bool foreman_metric_query_setuntil(ForemanMetricQuery* q, time_t ts)
{
  if (!q)
    return false;
  ((Query*)q)->until = ts;
  return true;
}

////////////////////////////////////////////////
// foreman_metric_query_getuntil
////////////////////////////////////////////////

bool foreman_metric_query_getuntil(ForemanMetricQuery* q, time_t* ts)
{
  if (!q)
    return false;
  *ts = ((Query*)q)->until;
  return true;
}

////////////////////////////////////////////////
// foreman_metric_query_setinterval
////////////////////////////////////////////////

bool foreman_metric_query_setinterval(ForemanMetricQuery* q, time_t ts)
{
  if (!q)
    return false;
  ((Query*)q)->interval = ts;
  return true;
}

////////////////////////////////////////////////
// foreman_metric_query_getinterval
////////////////////////////////////////////////

bool foreman_metric_query_getinterval(ForemanMetricQuery* q, time_t* ts)
{
  if (!q)
    return false;
  *ts = ((Query*)q)->interval;
  return true;
}
