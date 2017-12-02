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

#include <foreman/Const.h>
#include <foreman/action/impl/Python.h>
#include <foreman/common/Errors.h>

#if defined(FOREMAN_SUPPORT_PYTHON)

const std::string Foreman::Action::PythonEngine::LANGUAGE = "python";
const std::string Foreman::Action::PythonEngine::MODULE = FOREMANCC_PRODUCT_NAME;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Foreman::Action::PythonEngine::PythonEngine()
    : ScriptEngine(LANGUAGE)
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

bool Foreman::Action::PythonEngine::compile(Script* script, Error* err)
{
  PythonScript *pyScript = dynamic_cast<PythonScript *>(script);
  if (!pyScript) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  return pyScript->compile(err);
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

bool Foreman::Action::PythonEngine::run(const Script* script, const Parameters* params, Parameters* results, Error* error) const
{
  lock();

  unlock();

  return false;
}

////////////////////////////////////////////////
// getLastError
////////////////////////////////////////////////

bool Foreman::Action::PythonEngine::setLastDetailError(Error* error) const
{
  PyObject *ptype, *pvalue, *ptraceback;
  PyErr_Fetch(&ptype, &pvalue, &ptraceback);
  error->setDetailMessage(PyString_AsString(pvalue));

#if defined(DEBUG)
  PyObject_Print(ptype, stdout, 0);
  PyObject_Print(pvalue, stdout, 0);
  PyObject_Print(ptraceback, stdout, 0);
#endif

  return true;
}

#endif
