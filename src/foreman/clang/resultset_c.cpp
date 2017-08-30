/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/ResultSet.h>
#include <foreman/foreman-c.h>

using namespace Foreman;

////////////////////////////////////////////////
// foreman_resultset_new
////////////////////////////////////////////////

ForemanResultSet* foreman_resultset_new()
{
  return new ResultSet();
}

////////////////////////////////////////////////
// foreman_resultset_delete
////////////////////////////////////////////////

bool foreman_resultset_delete(ForemanResultSet* rs)
{
  if (!rs)
    return false;
  delete (ResultSet*)rs;
  return true;
}

////////////////////////////////////////////////
// foreman_resultset_getnvalues
////////////////////////////////////////////////

size_t foreman_resultset_getnvalues(ForemanResultSet* rs)
{
  if (!rs)
    return 0;
  return ((ResultSet*)rs)->valueCount;
}

////////////////////////////////////////////////
// foreman_resultset_getvalue
////////////////////////////////////////////////

bool foreman_resultset_getvalue(ForemanResultSet* rs, size_t n, double* value)
{
  if (!rs)
    return false;
  
  if (foreman_resultset_getnvalues(rs) <= n)
    return false;
  
  *value = ((ResultSet*)rs)->values[n];
  
  return true;
}

////////////////////////////////////////////////
// foreman_resultset_getvalues
////////////////////////////////////////////////

double* foreman_resultset_getnvalue(ForemanResultSet* rs)
{
  if (!rs)
    return 0;
  return ((ResultSet*)rs)->values;
}
