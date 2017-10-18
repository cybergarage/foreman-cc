/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Query.h>
#include <foreman/foreman-c.h>

using namespace Foreman;

////////////////////////////////////////////////
// foreman_query_new
////////////////////////////////////////////////

ForemanQuery* foreman_query_new()
{
  return new Query();
}

////////////////////////////////////////////////
// foreman_query_delete
////////////////////////////////////////////////

bool foreman_query_delete(ForemanQuery* q)
{
  if (!q)
    return false;
  delete (Query*)q;
  return true;
}

////////////////////////////////////////////////
// foreman_query_settarget
////////////////////////////////////////////////

bool foreman_query_settarget(ForemanQuery* q, const char* name)
{
  if (!q || !name)
    return false;
  ((Query*)q)->target = name;
  return true;
}

////////////////////////////////////////////////
// foreman_query_gettarget
////////////////////////////////////////////////

bool foreman_query_gettarget(ForemanQuery* q, const char** name)
{
  if (!q || !name)
    return false;
  *name = ((Query*)q)->target.c_str();
  return true;
}

////////////////////////////////////////////////
// foreman_query_setfrom
////////////////////////////////////////////////

bool foreman_query_setfrom(ForemanQuery* q, time_t ts)
{
  if (!q)
    return false;
  ((Query*)q)->from = ts;
  return true;
}

////////////////////////////////////////////////
// foreman_query_getfrom
////////////////////////////////////////////////

bool foreman_query_getfrom(ForemanQuery* q, time_t* ts)
{
  if (!q)
    return false;
  *ts = ((Query*)q)->from;
  return true;
}

////////////////////////////////////////////////
// foreman_query_setuntil
////////////////////////////////////////////////

bool foreman_query_setuntil(ForemanQuery* q, time_t ts)
{
  if (!q)
    return false;
  ((Query*)q)->until = ts;
  return true;
}

////////////////////////////////////////////////
// foreman_query_getuntil
////////////////////////////////////////////////

bool foreman_query_getuntil(ForemanQuery* q, time_t* ts)
{
  if (!q)
    return false;
  *ts = ((Query*)q)->until;
  return true;
}

////////////////////////////////////////////////
// foreman_query_setinterval
////////////////////////////////////////////////

bool foreman_query_setinterval(ForemanQuery* q, time_t ts)
{
  if (!q)
    return false;
  ((Query*)q)->interval = ts;
  return true;
}

////////////////////////////////////////////////
// foreman_query_getinterval
////////////////////////////////////////////////

bool foreman_query_getinterval(ForemanQuery* q, time_t* ts)
{
  if (!q)
    return false;
  *ts = ((Query*)q)->interval;
  return true;
}
