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
#include <foreman/common/Errors.h>

////////////////////////////////////////////////
// ScriptManager
////////////////////////////////////////////////

Foreman::Action::ScriptManager::ScriptManager()
{
}

Foreman::Action::ScriptManager::~ScriptManager()
{
}

////////////////////////////////////////////////
// setScript
////////////////////////////////////////////////

bool Foreman::Action::ScriptManager::setScript(Script* script)
{
  if (!script)
    return false;

  const std::string& name = script->getName();
  if (name.length() <= 0) {
    return false;
  }

  const Script* currentScript = this->scripts.getScript(name);
  if (currentScript) {
    delete currentScript;
  }

  this->scripts[name] = script;

  return true;
}

////////////////////////////////////////////////
// setEngine
////////////////////////////////////////////////

bool Foreman::Action::ScriptManager::setEngine(ScriptEngine* engine)
{
  if (!engine)
    return false;

  const std::string& engineLang = engine->getLanguage();
  if (engineLang.length() <= 0) {
    return false;
  }

  const ScriptEngine* currentEngine = this->engines.getEngine(engineLang);
  if (currentEngine) {
    delete currentEngine;
  }

  this->engines[engineLang] = engine;

  return true;
}

////////////////////////////////////////////////
// setScript
////////////////////////////////////////////////

bool Foreman::Action::ScriptManager::setScript(const std::string& method, const std::string& lang, const std::string& code, int encodeType, Error* err)
{
  ScriptEngine* scriptEngine = this->engines.getEngine(lang);
  if (!scriptEngine) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  if (code.length() <= 0)
    return removeScript(method, err);

  Script *script = Foreman::Action::Script::CreateScript(lang);
  if (!script) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }
  script->setName(method);
  script->setCode(code);
  script->setEncording(encodeType);

  if (!scriptEngine->compile(script, err)) {
    delete script;
    return false;
  }

  if (!setScript(script)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    delete script;
    return false;
  }

  return true;
}

////////////////////////////////////////////////
// removeScript
////////////////////////////////////////////////

bool Foreman::Action::ScriptManager::removeScript(const std::string& method, Error* err)
{
  const Script* script = this->scripts.getScript(method);
  if (!script) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  return (this->scripts.erase(method) == 1) ? true : false;
}

bool Foreman::Action::ScriptManager::execMethod(const std::string& name, const Parameters* params, Parameters* results, Error* err)
{
  const Script* script = this->scripts.getScript(name);
  if (!script) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  const std::string& scriptLang = script->getLanguage();
  if (scriptLang.length() <= 0) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  const ScriptEngine* scriptEngine = this->engines.getEngine(scriptLang);
  if (!scriptEngine) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  return scriptEngine->run(script, params, results, err);
}
