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
// foreman_store_delete
////////////////////////////////////////////////

bool foreman_store_delete(ForemanStore* store)
{
  if (!store)
    return false;
  delete (Foreman::Store*)(store);
  return true;
}

////////////////////////////////////////////////
// foreman_store_setretentioninterval
////////////////////////////////////////////////

bool foreman_store_setretentioninterval(ForemanStore* store, time_t value)
{
  if (!store)
    return false;
  return ((Foreman::Store*)(store))->setRetentionInterval(value);
}

////////////////////////////////////////////////
// foreman_store_getretentioninterval
////////////////////////////////////////////////

time_t foreman_store_getretentioninterval(ForemanStore* store)
{
  if (!store)
    return 0;
  return ((Foreman::Store*)(store))->getRetentionInterval();
}

////////////////////////////////////////////////
// foreman_store_open
////////////////////////////////////////////////

bool foreman_store_open(ForemanStore* store)
{
  if (!store)
    return false;
  return ((Foreman::Store*)(store))->open();
}

////////////////////////////////////////////////
// foreman_store_close
////////////////////////////////////////////////

bool foreman_store_close(ForemanStore* store)
{
  if (!store)
    return false;
  return ((Foreman::Store*)(store))->close();
}

////////////////////////////////////////////////
// foreman_store_addmetric
////////////////////////////////////////////////

bool foreman_store_addmetric(ForemanStore* store, ForemanMetric* m)
{
  if (!store || !m)
    return false;

  if (((Foreman::Store*)(store))->addValue(*((const Foreman::Metric*)(m))))
    return true;

  std::shared_ptr<Foreman::Metric> cm = std::shared_ptr<Foreman::Metric>(new Foreman::Metric(*((const Foreman::Metric*)(m))));
  if (!((Foreman::Store*)(store))->addMetric(cm))
    return false;

  return ((Foreman::Store*)(store))->addValue(*((const Foreman::Metric*)(m)));
}

////////////////////////////////////////////////
// foreman_store_query
////////////////////////////////////////////////

bool foreman_store_query(ForemanStore* store, ForemanQuery* q, ForemanResultSet* rs)
{
  if (!store || !q || !rs)
    return false;

  if (!((Foreman::Store*)(store))->getValues(((Foreman::Query*)(q)), ((Foreman::ResultSet*)(rs))))
    return false;

  return true;
}
