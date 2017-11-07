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
#include <foreman/registry/Query.h>

using namespace Foreman::Registry;

////////////////////////////////////////////////
// foreman_registry_query_new
////////////////////////////////////////////////

ForemanRegistryQuery* foreman_registry_query_new()
{
  return new Query();
}

////////////////////////////////////////////////
// foreman_registry_query_delete
////////////////////////////////////////////////

bool foreman_registry_query_delete(ForemanRegistryQuery* q)
{
  if (!q)
    return false;
  delete (Query*)q;
  return true;
}
