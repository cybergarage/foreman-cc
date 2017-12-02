/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ACTION_PYTHON_H_
#define _FOREMANCC_ACTION_PYTHON_H_

#include <foreman/Platform.h>

#if defined(FOREMAN_SUPPORT_PYTHON)

#include <foreman/action/Script.h>
#include <string>

#if defined(FOREMAN_SUPPORT_PYTHON)
#if defined(HAVE_PYTHON_PYTHON_H)
#include <Python/Python.h>
#else
#include <Python.h>
#endif
#endif

namespace Foreman {
namespace Action {

  ////////////////////////////////////////////////
  // PtyhonScript
  ////////////////////////////////////////////////
  
  class PythonScript : public Script {
public:
    PythonScript();
    ~PythonScript();

    bool clear();

    bool compile(Error* error);
    bool isCompiled() const;

private:
    PyObject* module_;
    PyObject* func_;
  };

  ////////////////////////////////////////////////
  // PythonEngine
  ////////////////////////////////////////////////
  
  class PythonEngine : public ScriptEngine {

public:
    static const std::string LANGUAGE;
    static const std::string MODULE;

public:
    PythonEngine();
    ~PythonEngine();

    bool compile(Script* script, Error* error);
    bool run(const Script* script, const Parameters* params, Parameters* results, Error* error) const;

private:
    bool setLastDetailError(Error* error) const;
  };
}
}

#endif

#endif
