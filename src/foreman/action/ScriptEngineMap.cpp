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

Foreman::Action::ScriptEngineMap::ScriptEngineMap()
{
  init();
}

Foreman::Action::ScriptEngineMap::~ScriptEngineMap()
{
  clear();
}

void Foreman::Action::ScriptEngineMap::init()
{
}

bool Foreman::Action::ScriptEngineMap::hasEngine(const std::string& lang) const
{
  return (find(lang) != end()) ? true : false;
}

const Foreman::Action::ScriptEngine* Foreman::Action::ScriptEngineMap::getEngine(const std::string& lang) const
{
  ScriptEngineMap::const_iterator engineIt = find(lang);
  if (engineIt == end())
    return NULL;
  return engineIt->second;
}

void Foreman::Action::ScriptEngineMap::clear()
{
  for (ScriptEngineMap::iterator engineIt = begin(); engineIt != end(); engineIt++) {
    ScriptEngine* script = engineIt->second;
    if (script)
      delete script;
  }

  std::map<std::string, ScriptEngine*>::clear();
}
