/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Foreman.h>
#include <foreman/foreman-c.h>

using namespace Foreman;

////////////////////////////////////////////////
// foreman_store_matrix_create
////////////////////////////////////////////////

ForemanStore* foreman_store_matrix_create()
{
  return new MatrixStore();
}

////////////////////////////////////////////////
// foreman_store_ringmap_create
////////////////////////////////////////////////

ForemanStore* foreman_store_ringmap_create()
{
  return new RingMapStore();
}

////////////////////////////////////////////////
// foreman_store_sqlite_create
////////////////////////////////////////////////

ForemanStore* foreman_store_sqlite_create()
{
  return new NarrowTableStore();
}

////////////////////////////////////////////////
// foreman_store_tsmap_create
////////////////////////////////////////////////

#if defined(FOREMAN_ENABLE_BERINGEI)

ForemanStore* foreman_store_tsmap_create()
{
  return new TSmapStore();
}

#endif
