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

using namespace Foreman::Action;

#if defined(FOREMAN_SUPPORT_PYTHON)

////////////////////////////////////////////////
// PythonParameters
////////////////////////////////////////////////

PythonParameters::PythonParameters()
{
  this->dict_ = PyDict_New();
}

PythonParameters::~PythonParameters()
{
  Py_DECREF(this->dict_);
}

////////////////////////////////////////////////
// set
////////////////////////////////////////////////

bool PythonParameters::set(const Parameters* params)
{
  for (auto param : *params) {
  }

  return true;
}

////////////////////////////////////////////////
// get
////////////////////////////////////////////////

bool PythonParameters::get(Parameters* params)
{
  PyObject *pyKey, *pyValue;
  Py_ssize_t pos = 0;

  while (PyDict_Next(this->dict_, &pos, &pyKey, &pyValue)) {
  }

  return true;
}

////////////////////////////////////////////////
// equals
////////////////////////////////////////////////

bool PythonParameters::equals(const Parameters* params)
{
  for (auto param : *params) {
    PyObject* pyObj = PyDict_GetItemString(this->dict_, param->getName());
    if (!pyObj)
      return false;
  }

  return true;
}

#endif
