/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Const.h>
#include <foreman/registry/impl/SQLStore.h>

using namespace Foreman::Registry;

////////////////////////////////////////////////
// SQLStore
////////////////////////////////////////////////

SQLStore::SQLStore()
{
}

SQLStore::~SQLStore()
{
}

////////////////////////////////////////////////
// getVersion
////////////////////////////////////////////////

const char* SQLStore::getVersion()
{
  return FOREMANCC_PRODUCT_VERSION;
}
