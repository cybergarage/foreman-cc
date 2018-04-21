/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Platform.h>

#include <foreman/action/impl/System.h>

////////////////////////////////////////////////
// SystemMethod
////////////////////////////////////////////////

Foreman::Action::SystemMethod::SystemMethod()
    : Foreman::Action::Method(Foreman::Action::SystemEngine::LANGUAGE)
{
}

Foreman::Action::SystemMethod::~SystemMethod()
{
}
