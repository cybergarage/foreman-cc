/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Platform.h>

#if defined(FOREMAN_SUPPORT_PYTHON)

#include <foreman/action/impl/Python.h>

using namespace Foreman::Action;

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
    Py_CLEAR(this->obj_);
    this->obj_ = NULL;
  }
  return true;
}

////////////////////////////////////////////////
// getPyObject
////////////////////////////////////////////////

PyObject* PythonParameter::getPyObject() const
{
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
    Py_XINCREF(this->obj_);
    setType(BoolType);
    return true;
  }

  if (PyInt_Check(pyObj)) {
    this->obj_ = pyObj;
    Py_XINCREF(this->obj_);
    setType(IntegerType);
    return true;
  }

  if (PyFloat_Check(pyObj)) {
    this->obj_ = pyObj;
    Py_XINCREF(this->obj_);
    setType(RealType);
    return true;
  }

  if (PyString_Check(pyObj)) {
    this->obj_ = pyObj;
    Py_XINCREF(this->obj_);
    setType(StringType);
    return true;
  }

  if (PyDict_Check(pyObj)) {
    this->obj_ = pyObj;
    Py_XINCREF(this->obj_);
    setType(DictType);
    return true;
  }

  if (PyList_Check(pyObj)) {
    this->obj_ = pyObj;
    Py_XINCREF(this->obj_);
    setType(ListType);
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

  switch (param->getType()) {
  case IntegerType: {
    auto iparam = dynamic_cast<const Integer*>(param);
    if (!iparam)
      return false;
    pyObj = PyInt_FromLong(iparam->getValue());

  } break;
  case RealType: {
    auto rparam = dynamic_cast<const Real*>(param);
    if (!rparam)
      return false;
    pyObj = PyFloat_FromDouble(rparam->getValue());
  } break;
  case BoolType: {
    auto bparam = dynamic_cast<const Bool*>(param);
    if (!bparam)
      return false;
    pyObj = bparam->getValue() ? Py_True : Py_False;

  } break;
  case StringType: {
    auto sparam = dynamic_cast<const String*>(param);
    if (!sparam)
      return false;
    pyObj = PyString_FromString(sparam->getValue().c_str());
  } break;
  default:
    return false;
  }

  if (!pyObj)
    return false;

  if (!setValue(pyObj)) {
    return false;
  }

  Py_XDECREF(pyObj);

  return true;
}

////////////////////////////////////////////////
// get
////////////////////////////////////////////////

bool PythonParameter::get(Parameter** param)
{
  *param = NULL;

  switch (getType()) {
  case IntegerType: {
    auto iparam = new Integer();
    if (!iparam)
      return false;
    iparam->setValue(PyInt_AsLong(this->obj_));
    *param = iparam;
  } break;
  case RealType: {
    auto rparam = new Real();
    if (!rparam)
      return false;
    rparam->setValue(PyFloat_AsDouble(this->obj_));
    *param = rparam;
  } break;
  case BoolType: {
    auto bparam = new Bool();
    if (!bparam)
      return false;
    auto bvalue = (this->obj_ == Py_True) ? true : false;
    bparam->setValue(bvalue);
    *param = bparam;
  } break;
  case StringType: {
    auto sparam = new String();
    if (!sparam)
      return false;
    sparam->setValue(PyString_AsString(this->obj_));
    *param = sparam;
  } break;
    // FIXME : Not implemented yet
  case DictType: {
    auto dparam = new Dict();
    if (!dparam)
      return false;
    *param = dparam;
  } break;
    // FIXME : Not implemented yet
  case ListType: {
    auto lparam = new List();
    if (!lparam)
      return false;
    *param = lparam;
  } break;
  default:
    return false;
  }

  if (!(*param))
    return false;

  (*param)->setName(getName());

  return true;
}

////////////////////////////////////////////////
// equals
////////////////////////////////////////////////

bool PythonParameter::equals(const Parameter* param)
{
  if (getType() != param->getType())
    return false;

  switch (getType()) {
  case IntegerType: {
    auto iparam = dynamic_cast<const Integer*>(param);
    if (!iparam)
      return false;
    if (PyInt_AsLong(this->obj_) != iparam->getValue())
      return false;
    return true;
  } break;
  case RealType: {
    auto rparam = dynamic_cast<const Real*>(param);
    if (!rparam)
      return false;
    if (PyFloat_AsDouble(this->obj_) != rparam->getValue())
      return false;
    return true;
  } break;
  case BoolType: {
    auto bparam = dynamic_cast<const Bool*>(param);
    if (!bparam)
      return false;
    auto bvalue = (this->obj_ == Py_True) ? true : false;
    if (bvalue != bparam->getValue())
      return false;
    return true;
  } break;
  case StringType: {
    auto sparam = dynamic_cast<const String*>(param);
    if (!sparam)
      return false;
    const char* pyValue = PyString_AsString(this->obj_);
    if (!pyValue)
      return false;
    auto value = sparam->getValue();
    if (value.compare(pyValue) != 0)
      return false;
    return true;
  } break;
  default:
    return false;
  }

  return false;
}

#endif
