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
// foreman_resultset_getdatapointcount
////////////////////////////////////////////////

size_t foreman_resultset_getdatapointcount(ForemanResultSet* rs)
{
  if (!rs)
    return 0;
  return ((ResultSet*)rs)->getDataPointCount();
}

////////////////////////////////////////////////
// foreman_resultset_firstdatapoint
////////////////////////////////////////////////

ForemanDataPoint* foreman_resultset_firstdatapoint(ForemanResultSet* rs)
{
  if (!rs)
    return NULL;

  return ((ResultSet*)rs)->firstDataPoint();
}

////////////////////////////////////////////////
// foreman_resultset_nextdatapoint
////////////////////////////////////////////////

ForemanDataPoint* foreman_resultset_nextdatapoint(ForemanResultSet* rs)
{
  if (!rs)
    return NULL;

  return ((ResultSet*)rs)->nextDataPoint();
}

////////////////////////////////////////////////
// foreman_resultset_finddatapoint
////////////////////////////////////////////////

ForemanDataPoint* foreman_resultset_finddatapoint(ForemanResultSet* rs, const char* name)
{
  if (!rs)
    return NULL;

  return ((ResultSet*)rs)->findDataPoints(name);
}
