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

#include <foreman/Const.h>
#include <foreman/action/impl/System.h>
#include <foreman/common/Errors.h>

#include <stdlib.h>
#include <string.h>

const std::string Foreman::Action::SystemEngine::LANGUAGE = FOREMANCC_ACTION_SCRIPT_ENGINE_SYSTEM;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Foreman::Action::SystemEngine::SystemEngine()
    : ScriptEngine(LANGUAGE)
{
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

Foreman::Action::SystemEngine::~SystemEngine()
{
}

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

bool Foreman::Action::SystemEngine::compile(Method* luaScript, Error* error)
{
  return true;
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

bool Foreman::Action::SystemEngine::run(Method* method, const Parameters* params, Parameters* results, Error* error)
{
  auto code = (char*)method->getCode();
  if (!code || (::strlen(code) <= 0))
    return false;

  auto ret = ::system(code);
  if (ret < 0)
    return false;

  return (ret == 0) ? true : false;
}
