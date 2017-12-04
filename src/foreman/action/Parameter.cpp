/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/action/Parameter.h>

using namespace Foreman::Action;

////////////////////////////////////////////////
// Parameter
////////////////////////////////////////////////

Parameter::Parameter()
{
  setType(UnknownType);
}

Parameter::Parameter(ParameterType type)
{
  setType(type);
}

Parameter::~Parameter() {}
