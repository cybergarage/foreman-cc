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
  // PythonParameter
  ////////////////////////////////////////////////

  class PythonParameter : public Parameter {
public:
    PythonParameter();
    ~PythonParameter();

    bool setName(const std::string& name)
    {
      Parameter::setName(name);
      return true;
    }

    bool setName(PyObject* pyObj);
    bool setValue(PyObject* pyObj);

    bool set(const Parameter* param);
    bool get(Parameter** param);

    bool equals(const Parameter* param);

    PyObject* getPyObject()
    {
      return obj_;
    }

private:
    bool clear();

private:
    PyObject* obj_;
  };

  ////////////////////////////////////////////////
  // PythonParameters
  ////////////////////////////////////////////////

  class PythonParameters {
public:
    PythonParameters();
    ~PythonParameters();

    bool set(const Parameters* params);
    bool get(Parameters* params);

    bool equals(const Parameters* params);

    PyObject* getPyObject()
    {
      return dict_;
    }

private:
    PyObject* dict_;
  };

  ////////////////////////////////////////////////
  // PythonScript
  ////////////////////////////////////////////////

  class PythonScript : public Script {
public:
    PythonScript();
    ~PythonScript();

    bool clear();

    bool compile(Error* error);
    bool isCompiled() const;

    PyObject* getModuleObject()
    {
      return module_;
    }

    PyObject* getFuncObject()
    {
      return func_;
    }

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
    bool run(Script* script, const Parameters* params, Parameters* results, Error* error);

private:
    bool setLastDetailError(Error* error) const;
  };
}
}

#endif

#endif
