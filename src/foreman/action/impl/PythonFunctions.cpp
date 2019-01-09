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

#include <foreman/Client.h>
#include <foreman/Const.h>
#include <foreman/action/impl/GlobalObject.h>
#include <foreman/action/impl/Python.h>
#include <foreman/common/Error.h>
#include <foreman/util/Log.h>

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

  LOG_INFO("SET KEY : %s = %s (%d)", key, val, int(isSuccess));

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

  LOG_INFO("GET KEY : %s = %s (%d)", key, (regData ? regData : ""), int(isSuccess));

  return Py_BuildValue("s", regData);
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

  LOG_INFO("REMOVE KEY : %s (%d)", key, int(isSuccess));

  return Py_BuildValue("i", isSuccess);
}

/****************************************
 * foreman_python_executequery
 ****************************************/

#define FOREMANCC_PYTHON_PARSEJSON_METHOD "_foreman_python_parsejson"
#define FOREMANCC_PYTHON_PARSEJSON_MODULE FOREMANCC_PRODUCT_NAME "_internal"

#if !defined(DEBUG)
#define FOREMANCC_PYTHON_PARSEJSON_METHOD_CODE        \
  "import json\n"                                     \
  "def " FOREMANCC_PYTHON_PARSEJSON_METHOD "(str):\n" \
  "    return json.loads(str)\n"
#else
#define FOREMANCC_PYTHON_PARSEJSON_METHOD_CODE        \
  "import json\n"                                     \
  "def " FOREMANCC_PYTHON_PARSEJSON_METHOD "(str):\n" \
  "    jsonObj = json.loads(str)\n"                   \
  "    print(jsonObj)\n"                              \
  "    return jsonObj\n"
#endif

bool foreman_python_string2jsonobject(const std::string& jsonStr, PyObject** pyObj, Foreman::Error* err)
{
  static PyObject* pyJsonModule = NULL;
  static PyObject* pyJsonFunc = NULL;

  *pyObj = NULL;
  
  if (jsonStr.size() <= 0) {
    return true;
  }
  
  if (!pyJsonFunc) {
    PyObject* pSource = Py_CompileString(FOREMANCC_PYTHON_PARSEJSON_METHOD_CODE, FOREMANCC_PYTHON_PARSEJSON_METHOD, Py_file_input);
    if (!pSource) {
      foreman_python_getlasterror(err);
      return false;
    }

    auto moduleName = Foreman::Action::PythonEngine::SYSTEM_MODULE.c_str();
    pyJsonModule = PyImport_ExecCodeModule((char*)moduleName, pSource);
    Py_DECREF(pSource);
    if (!pyJsonModule) {
      foreman_python_getlasterror(err);
      return false;
    }

    pyJsonFunc = PyObject_GetAttrString(pyJsonModule, FOREMANCC_PYTHON_PARSEJSON_METHOD);
    if (!pyJsonFunc || !PyCallable_Check(pyJsonFunc)) {
      foreman_python_getlasterror(err);
      Py_DECREF(pyJsonModule);
      pyJsonModule = NULL;
      return false;
    }
  }

  PyObject* pArgs = PyTuple_New(1);
  if (!pArgs) {
    foreman_python_getlasterror(err);
    return false;
  }

  PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(jsonStr.c_str()));
  PyObject* pResults = PyObject_CallObject(pyJsonFunc, pArgs);
  Py_DECREF(pArgs);

  *pyObj = pResults;
  
  return true;
}

PyObject* foreman_python_executequery(PyObject* self, PyObject* args)
{
  Foreman::Error err;

  const char* query;
  if (!PyArg_ParseTuple(args, "s", &query))
    return NULL;

  // Query

  std::string jsonRes;
  Foreman::Client client;
  LOG_INFO("%s", query);
  if (!client.query(query, &jsonRes)) {
    return NULL;
  }
  LOG_INFO("%s", jsonRes.c_str());

  // Parse the JSON response

  PyObject* resObj;
  
  if (!foreman_python_string2jsonobject(jsonRes, &resObj, &err)) {
    foreman_python_getlasterror(&err);
    return NULL;
  }
  
  return resObj;
}

/****************************************
 * foreman_python_postquery
 ****************************************/

PyObject* foreman_python_postquery(PyObject* self, PyObject* args)
{
  Foreman::Error err;

  const char* host;
  const char* query;
  int port;
  if (!PyArg_ParseTuple(args, "sis", &host, &port, &query))
    return NULL;

  // Query

  std::string jsonRes;
  Foreman::Client client;
  client.setHost(host);
  client.setPort(port);
  LOG_INFO("%s", query);
  if (!client.query(query, &jsonRes)) {
    return NULL;
  }
  LOG_INFO("%s", jsonRes.c_str());

  // Parse the JSON response

  PyObject* resObj;
  
  if (!foreman_python_string2jsonobject(jsonRes, &resObj, &err)) {
    foreman_python_getlasterror(&err);
    return NULL;
  }

  return resObj;
}

/****************************************
 * Python Modules
 ****************************************/

static PyMethodDef gForemanPythonMethods[] = {
  { FOREMANCC_SYSTEM_FUNCTION_SETREGISTER, foreman_python_setregister, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_GETREGISTER, foreman_python_getregister, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_REMOVEREGISTER, foreman_python_removeregister, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_EXECUTEQUERY, foreman_python_executequery, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_POSTQUERY, foreman_python_postquery, METH_VARARGS, "" },
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
