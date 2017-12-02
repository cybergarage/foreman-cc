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
// ScriptMap
////////////////////////////////////////////////

Foreman::Action::ScriptMap::ScriptMap()
{
}

Foreman::Action::ScriptMap::~ScriptMap()
{
  clear();
}

////////////////////////////////////////////////
// hasScript
////////////////////////////////////////////////

bool Foreman::Action::ScriptMap::hasScript(const std::string& name) const
{
  return (find(name) != end()) ? true : false;
}

////////////////////////////////////////////////
// getScript
////////////////////////////////////////////////

Foreman::Action::Script* Foreman::Action::ScriptMap::getScript(const std::string& name)
{
  ScriptMap::iterator scriptIt = find(name);
  if (scriptIt == end())
    return NULL;
  return scriptIt->second;
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

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
