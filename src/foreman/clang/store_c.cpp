/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Foreman.h>
#include <foreman/foreman-c.h>

using namespace Foreman;

////////////////////////////////////////////////
// foreman_store_addmetric
////////////////////////////////////////////////

bool foreman_store_addmetric(ForemanStore* store, ForemanMetric* m)
{
  if (!store || !m)
    return false;
  return ((Foreman::Store*)(store))->addValue(*((const Foreman::Metric*)(m)));
}

////////////////////////////////////////////////
// foreman_store_addmetric
////////////////////////////////////////////////

bool foreman_store_query(ForemanStore* store, ForemanQuery* q, ForemanResultSet* rs)
{
  if (!store || !q || !rs)
    return false;
  return true;
}
