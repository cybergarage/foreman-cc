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

#include <foreman/Const.h>
#include <foreman/action/impl/GlobalObject.h>
#include <foreman/action/impl/Python.h>

/****************************************
 * foreman_python_setregistry
 ****************************************/

PyObject* foreman_python_setregister(PyObject* self, PyObject* args)
{
  const char *key, *val;

  if (!PyArg_ParseTuple(args, "ss", &key, &val))
    return NULL;

  auto store = Foreman::Action::GetGlobalRegisterStore();
  if (!store)
    return NULL;

  Foreman::Register::Object obj;
  obj.setKey(key);
  obj.setData(val);

  Foreman::Error err;
  bool isSuccess = store->setObject(&obj, &err);

  return Py_BuildValue("i", isSuccess);
}

/****************************************
 * foreman_python_getregistry
 ****************************************/

PyObject* foreman_python_getregister(PyObject* self, PyObject* args)
{
  const char* key;

  if (!PyArg_ParseTuple(args, "s", &key))
    return NULL;

  auto store = Foreman::Action::GetGlobalRegisterStore();
  if (!store)
    return NULL;

  Foreman::Register::Object obj;
  Foreman::Error err;
  bool isSuccess = store->getObject(key, &obj, &err);

  const char* regData = NULL;
  if (isSuccess) {
    regData = obj.getData();
  }

  return Py_BuildValue("s", (regData ? regData : ""));
}

/****************************************
 * foreman_python_removeregistry
 ****************************************/

PyObject* foreman_python_removeregister(PyObject* self, PyObject* args)
{
  const char* key;

  if (!PyArg_ParseTuple(args, "s", &key))
    return NULL;

  auto store = Foreman::Action::GetGlobalRegisterStore();
  if (!store)
    return NULL;

  Foreman::Error err;
  bool isSuccess = store->removeObject(key, &err);

  return Py_BuildValue("i", isSuccess);
}

/****************************************
 * foreman_python_executequery
 ****************************************/

#define foreman_python_parsejson_module FOREMANCC_PRODUCT_NAME "_internal"
#define foreman_python_parsejson_method "foreman_python_parsejson"
#define foreman_python_parsejson_code    \
  "import json\n"                        \
  "def foreman_python_parsejson(str):\n" \
  "    return json.loads(str)\n"

PyObject* foreman_python_executequery(PyObject* self, PyObject* args)
{
  const char* query;
  if (!PyArg_ParseTuple(args, "s", &query))
    return NULL;

  // Comile

  PyObject* pSource = Py_CompileString(foreman_python_parsejson_code, foreman_python_parsejson_method, Py_file_input);
  if (!pSource) {
    return NULL;
  }

  PyObject* pyModule = PyImport_ExecCodeModuleEx((char*)foreman_python_parsejson_module, pSource, (char*)foreman_python_parsejson_method);
  Py_DECREF(pSource);
  if (pyModule) {
    return NULL;
  }

  PyObject* pyFunc = PyObject_GetAttrString(pyModule, foreman_python_parsejson_method);
  if (!pyFunc || !PyCallable_Check(pyFunc)) {
    Py_DECREF(pyModule);
    return NULL;
  }

  // Exec method

  PyObject* pArgs = PyTuple_New(2);
  if (!pArgs) {
    return NULL;
  }

  PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(query));

  PyObject* pResults = PyObject_CallObject(pyFunc, pArgs);

  Py_DECREF(pyFunc);
  Py_DECREF(pyModule);
  Py_DECREF(pArgs);

  if (!pResults) {
    return NULL;
  }

  Py_DECREF(pResults);

  return pResults;
}

/****************************************
 * Python Modules
 ****************************************/

static PyMethodDef gForemanPythonMethods[] = {
  { FOREMANCC_SYSTEM_FUNCTION_SETREGISTER, foreman_python_setregister, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_GETREGISTER, foreman_python_getregister, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_REMOVEREGISTER, foreman_python_removeregister, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_EXECUTEQUERY, foreman_python_executequery, METH_VARARGS, "" },
  { NULL, NULL, 0, NULL }
};

PyMethodDef* Foreman::Action::GetPythonSystemMethods()
{
  return gForemanPythonMethods;
}

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef gForemanPythonModule = {
  PyModuleDef_HEAD_INIT,
  FOREMANCC_PRODUCT_NAME, /* m_name */
  FOREMANCC_PRODUCT_NAME, /* m_doc */
  -1, /* m_size */
  gForemanPythonMethods, /* m_methods */
  NULL, /* m_reload */
  NULL, /* m_traverse */
  NULL, /* m_clear */
  NULL, /* m_free */
};

PyModuleDef* Foreman::Action::GetPythonSystemModule()
{
  return &gForemanPythonModule;
}
#endif

#endif
