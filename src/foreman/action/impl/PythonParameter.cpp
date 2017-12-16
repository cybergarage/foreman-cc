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
// PythonParameter
////////////////////////////////////////////////

PythonParameter::PythonParameter()
{
  this->obj_ = NULL;
}

PythonParameter::~PythonParameter()
{
  clear();
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool PythonParameter::clear()
{
  if (this->obj_) {
    Py_XDECREF(this->obj_);
    this->obj_ = NULL;
  }
  return true;
}

////////////////////////////////////////////////
// getPyObject
////////////////////////////////////////////////

PyObject* PythonParameter::getPyObject() const
{
  Py_XINCREF(this->obj_);
  return this->obj_;
}

////////////////////////////////////////////////
// setName
////////////////////////////////////////////////

bool PythonParameter::setName(const std::string& name)
{
  Parameter::setName(name);
  return true;
}

////////////////////////////////////////////////
// setName
////////////////////////////////////////////////

bool PythonParameter::setName(PyObject* pyObj)
{
  if (!pyObj)
    return false;

  if (!PyString_Check(pyObj))
    return false;

  setName(PyString_AsString(pyObj));

  return true;
}

////////////////////////////////////////////////
// setValue
////////////////////////////////////////////////

bool PythonParameter::setValue(PyObject* pyObj)
{
  if (!pyObj)
    return false;

  if (PyBool_Check(pyObj)) {
    this->obj_ = pyObj;
    Parameter::setValue(this->obj_ == Py_True);
    return true;
  }

  if (PyInt_Check(pyObj)) {
    this->obj_ = pyObj;
    Parameter::setValue(PyInt_AsLong(this->obj_));
    return true;
  }

  if (PyFloat_Check(pyObj)) {
    this->obj_ = pyObj;
    Parameter::setValue(PyFloat_AsDouble(this->obj_));
    return true;
  }

  if (PyString_Check(pyObj)) {
    this->obj_ = pyObj;
    Parameter::setValue(PyString_AsString(this->obj_));
    return true;
  }

  return false;
}

////////////////////////////////////////////////
// set
////////////////////////////////////////////////

bool PythonParameter::set(const Parameter* param)
{
  if (!param)
    return false;

  clear();

  setName(param->getName());

  PyObject* pyObj = NULL;
  type_ = param->getType();
  value_ = param->getValue();

  switch (type_) {
  case IntegerType:
    pyObj = PyInt_FromLong(boost::get<long>(value_));
  case RealType:
    pyObj = PyFloat_FromDouble(boost::get<double>(value_));
  case StringType:
    pyObj = PyString_FromString(boost::get<std::string>(value_).c_str());
  case BoolType:
    pyObj = boost::get<bool>(value_) ? Py_True : Py_False;
  }

  if (!pyObj)
    return false;

  if (!setValue(pyObj)) {
    Py_DECREF(pyObj);
    return false;
  }

  return true;
}

////////////////////////////////////////////////
// get
////////////////////////////////////////////////

bool PythonParameter::get(Parameter** param)
{
  *param = new Parameter();

  (*param)->setValue(value_);
  (*param)->setName(getName());

  return true;
}

////////////////////////////////////////////////
// equals
////////////////////////////////////////////////

bool PythonParameter::equals(const Parameter* param)
{
  return param->getValue() == value_;
}

#endif
