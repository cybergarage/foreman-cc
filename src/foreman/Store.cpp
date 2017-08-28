/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <math.h>

#include <foreman/Store.h>

using namespace Foreman;

////////////////////////////////////////////////
// Store
////////////////////////////////////////////////

Store::Store()
{
}

Store::~Store()
{
}

////////////////////////////////////////////////
// addValues
////////////////////////////////////////////////

bool Store::addValues(const Metrics& values)
{
  for (std::shared_ptr<Foreman::Metric> value : values) {
    if (!addValue(*value))
      return false;
  }

  return true;
}
