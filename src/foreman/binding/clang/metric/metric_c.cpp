/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/Metric.h>
#include <foreman/metric/metric-c.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// foreman_metric_new
////////////////////////////////////////////////

ForemanMetric* foreman_metric_new()
{
  return new Metric();
}

////////////////////////////////////////////////
// foreman_metric_delete
////////////////////////////////////////////////

bool foreman_metric_delete(ForemanMetric* m)
{
  if (!m)
    return false;
  delete (Metric*)m;
  return true;
}

////////////////////////////////////////////////
// foreman_metric_setname
////////////////////////////////////////////////

bool foreman_metric_setname(ForemanMetric* m, const char* name)
{
  if (!m || !name)
    return false;
  ((Metric*)m)->name = name;
  return true;
}

////////////////////////////////////////////////
// foreman_metric_setvalue
////////////////////////////////////////////////

bool foreman_metric_setvalue(ForemanMetric* m, double value)
{
  if (!m)
    return false;
  ((Metric*)m)->value = value;
  return true;
}

////////////////////////////////////////////////
// foreman_metric_settimestamp
////////////////////////////////////////////////

bool foreman_metric_settimestamp(ForemanMetric* m, time_t ts)
{
  if (!m)
    return false;
  ((Metric*)m)->timestamp = ts;
  return true;
}

////////////////////////////////////////////////
// foreman_metric_getname
////////////////////////////////////////////////

bool foreman_metric_getname(ForemanMetric* m, const char** name)
{
  if (!m || !name)
    return false;
  *name = ((Metric*)m)->name.c_str();
  return true;
}

////////////////////////////////////////////////
// foreman_metric_getvalue
////////////////////////////////////////////////

bool foreman_metric_getvalue(ForemanMetric* m, double* value)
{
  if (!m)
    return false;
  *value = ((Metric*)m)->value;
  return true;
}

////////////////////////////////////////////////
// foreman_metric_gettimestamp
////////////////////////////////////////////////

bool foreman_metric_gettimestamp(ForemanMetric* m, time_t* ts)
{
  if (!m)
    return false;
  *ts = ((Metric*)m)->timestamp;
  return true;
}
