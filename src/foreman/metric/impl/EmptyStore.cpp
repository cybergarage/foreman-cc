/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <sqlite3.h>
#include <stdio.h>

#include <foreman/Const.h>
#include <foreman/metric/impl/EmptyStore.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// EmptyStore
////////////////////////////////////////////////

EmptyStore::EmptyStore()
{
}

EmptyStore::~EmptyStore()
{
}
