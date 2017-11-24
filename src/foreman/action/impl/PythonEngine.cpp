/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>

#include <foreman/action/impl/Python.h>
#include <foreman/common/Errors.h>

#if defined(FOREMAN_SUPPORT_PYTHON)

const std::string Foreman::Action::PythonEngine::LANGUAGE = "python";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Foreman::Action::PythonEngine::PythonEngine(): ScriptEngine(LANGUAGE)
{
  Py_Initialize();
  
#if PY_MAJOR_VERSION >= 3
#else
#endif
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

Foreman::Action::PythonEngine::~PythonEngine()
{
  Py_Finalize();
}

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

bool Foreman::Action::PythonEngine::compile(const Script* luaScript) const
{
  return false;
}

bool Foreman::Action::PythonEngine::run(const Script* script, const Parameters* params, Parameters* results, Error* error) const
{
  lock();
  
  unlock();
  
  return false;
}

#endif

