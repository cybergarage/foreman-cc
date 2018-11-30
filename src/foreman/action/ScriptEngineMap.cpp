/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/action/Engine.h>

////////////////////////////////////////////////
// ScriptEngineMap
////////////////////////////////////////////////

Foreman::Action::ScriptEngineMap::ScriptEngineMap()
{
  init();
}

Foreman::Action::ScriptEngineMap::~ScriptEngineMap()
{
  clear();
}

////////////////////////////////////////////////
// init
////////////////////////////////////////////////

void Foreman::Action::ScriptEngineMap::init()
{
}

////////////////////////////////////////////////
// hasEngine
////////////////////////////////////////////////

bool Foreman::Action::ScriptEngineMap::hasEngine(const std::string& lang) const
{
  return (find(lang) != end()) ? true : false;
}

////////////////////////////////////////////////
// getEngine
////////////////////////////////////////////////

Foreman::Action::ScriptEngine* Foreman::Action::ScriptEngineMap::getEngine(const std::string& lang)
{
  auto engineIt = find(lang);
  if (engineIt == end())
    return NULL;
  auto engine = engineIt->second.get();
  return engine;
}
