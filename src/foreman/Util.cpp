/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Util.h>

////////////////////////////////////////////////
// CreateNanDataPointValueArray
////////////////////////////////////////////////

double* Foreman::CreateNanDataPointValueArray(size_t size)
{
  double* values = new double[size];
  if (!values)
    return NULL;

  for (size_t n = 0; n < size; n++) {
    values[n] = NAN;
  }

  return values;
}
