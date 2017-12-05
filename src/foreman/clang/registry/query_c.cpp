/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/registry/Query.h>
#include <foreman/registry/registry-c.h>

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

////////////////////////////////////////////////
// foreman_registry_query_setparentid
////////////////////////////////////////////////

bool foreman_registry_query_setparentid(ForemanRegistryQuery* q, const char* pid)
{
  if (!q)
    return false;
  ((Query*)q)->setParentId(pid);
  return true;
}

////////////////////////////////////////////////
// foreman_registry_query_getparentid
////////////////////////////////////////////////

bool foreman_registry_query_getparentid(ForemanRegistryQuery* q, const char** pid)
{
  if (!q || !pid)
    return false;
  *pid = ((Query*)q)->getParentId();
  return true;
}
