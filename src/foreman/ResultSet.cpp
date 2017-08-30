/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/ResultSet.h>
#include <stdlib.h>

using namespace Foreman;

////////////////////////////////////////////////
// ResultSet
////////////////////////////////////////////////

ResultSet::ResultSet()
{
  count = 0;
  values = NULL;
}

ResultSet::~ResultSet()
{
  clear();
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool ResultSet::clear()
{
  if (values) {
    free(values);
    values = NULL;
  }

  count = 0;

  return true;
}
