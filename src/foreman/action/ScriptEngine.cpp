/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/action/Script.h>

////////////////////////////////////////////////
// ScriptEngine
////////////////////////////////////////////////

Foreman::Action::ScriptEngine::ScriptEngine(const std::string& language)
{
  init();
  this->language = language;
}

void Foreman::Action::ScriptEngine::init()
{
}

Foreman::Action::ScriptEngine::~ScriptEngine()
{
}
