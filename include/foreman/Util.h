/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_UTIL_H_
#define _FOREMANCC_UTIL_H_

#include <math.h>
#include <stdlib.h>

namespace Foreman {

double* CreateNanDataPointValueArray(size_t size);

inline bool IsValidDataPointValue(double value)
{
  if (value == NAN)
    return false;
  return true;
}
}

#endif
