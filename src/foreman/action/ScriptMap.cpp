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

Foreman::Action::ScriptMap::ScriptMap()
{
}

Foreman::Action::ScriptMap::~ScriptMap()
{
  clear();
}

bool Foreman::Action::ScriptMap::hasScript(const std::string& name) const
{
  return (find(name) != end()) ? true : false;
}

const Foreman::Action::Script* Foreman::Action::ScriptMap::getScript(const std::string& name) const
{
  ScriptMap::const_iterator scriptIt = find(name);
  if (scriptIt == end())
    return NULL;
  return scriptIt->second;
}

void Foreman::Action::ScriptMap::clear()
{
  for (ScriptMap::iterator scriptIt = begin(); scriptIt != end(); scriptIt++) {
    Script* script = scriptIt->second;
    if (script) {
      delete script;
    }
  }
  std::map<std::string, Script*>::clear();
}
