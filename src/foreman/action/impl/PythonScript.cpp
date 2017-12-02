/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/action/impl/Python.h>

////////////////////////////////////////////////
// PythonScript
////////////////////////////////////////////////

Foreman::Action::PythonScript::PythonScript()
    : Foreman::Action::Script(Foreman::Action::PythonEngine::LANGUAGE)
{
  module_ = NULL;
  func_ = NULL;
}

Foreman::Action::PythonScript::~PythonScript()
{
  clear();
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool Foreman::Action::PythonScript::clear()
{
  module_ = NULL;
  func_ = NULL;
  
  return true;
}

////////////////////////////////////////////////
// isCompiled
////////////////////////////////////////////////

bool Foreman::Action::PythonScript::isCompiled() const
{
  if (!module_ || !func_)
    return false;

  return true;
}

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

bool Foreman::Action::PythonScript::compile(Error* error)
{
  /*
  const char *methodName= script->getName();
  const byte *sourceCode = script->getCode();
  
  char moduleName[64];
  snprintf(moduleName, sizeof(moduleName), "%s-%s", MODULE.c_str(), methodName);
  
  PyObject *pSource = Py_CompileString(sourceCode, methodName, Py_file_input);
  if (!pSource) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    setLastDetailError(err);
    return false;
  }
  
  *pModule = PyImport_ExecCodeModuleEx((char *)moduleName, pSource, (char *)methodName);
  Py_DECREF(pSource);
  if (!(*pModule)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    setLastDetailError(err);
    return false;
  }
  */
  
  return true;
}
