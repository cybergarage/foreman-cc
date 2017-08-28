/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <Foreman.h>
#include <foreman/foreman-c.h>

using namespace Foreman;

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
  delete m;
  return true;
}
