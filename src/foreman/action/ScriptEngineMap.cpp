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
// clear
////////////////////////////////////////////////

void Foreman::Action::ScriptEngineMap::clear()
{
  for (ScriptEngineMap::iterator engineIt = begin(); engineIt != end(); engineIt++) {
    ScriptEngine* script = engineIt->second;
    if (script)
      delete script;
  }

  std::map<std::string, ScriptEngine*>::clear();
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
  ScriptEngineMap::iterator engineIt = find(lang);
  if (engineIt == end())
    return NULL;
  return engineIt->second;
}
