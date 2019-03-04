/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_TEST_SCRIPT_MANAGERTESTCONTROLLER_H_
#define _FOREMANCC_TEST_SCRIPT_MANAGERTESTCONTROLLER_H_

#include <foreman/action/Manager.h>

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

#define FOREMANCC_TEST_SCRIPT_ERROR_METHOD "error_method"
#define FOREMANCC_TEST_SCRIPT_ECHO_METHOD "test_echo"
#define FOREMANCC_TEST_SCRIPT_ECHO_PARAM_NAME "message"
#define FOREMANCC_TEST_SCRIPT_ECHO_PARAM_VALUE "echo"

#define FOREMANCC_TEST_SCRIPT_SET_REGISTER_METHOD "test_setregister"
#define FOREMANCC_TEST_SCRIPT_SET_REGISTER_METHOD_PARAM_NAME "test_message"
#define FOREMANCC_TEST_SCRIPT_SET_REGISTER_METHOD_PARAM_VALUE "echo"

#define FOREMANCC_TEST_SCRIPT_GET_REGISTER_METHOD "test_getregister"
#define FOREMANCC_TEST_SCRIPT_GET_REGISTER_METHOD_PARAM_NAME FOREMANCC_TEST_SCRIPT_POST_REGISTER_METHOD_PARAM_NAME
#define FOREMANCC_TEST_SCRIPT_GET_REGISTER_METHOD_PARAM_VALUE FOREMANCC_TEST_SCRIPT_POST_REGISTER_METHOD_PARAM_VALUE

#define FOREMANCC_TEST_SCRIPT_REMOVE_REGISTER_METHOD "test_removeregister"
#define FOREMANCC_TEST_SCRIPT_REMOVE_REGISTER_METHOD_PARAM_NAME FOREMANCC_TEST_SCRIPT_POST_REGISTER_METHOD_PARAM_NAME

#define FOREMANCC_TEST_SCRIPT_EXECUTE_QUERY_METHOD "test_executequery"
#define FOREMANCC_TEST_SCRIPT_EXECUTE_QUERY_METHOD_PARAM_NAME "q"

#define FOREMANCC_TEST_SCRIPT_POST_QUERY_METHOD "test_postquery"
#define FOREMANCC_TEST_SCRIPT_POST_QUERY_METHOD_QUERY_PARAM_NAME "q"
#define FOREMANCC_TEST_SCRIPT_POST_QUERY_HOST "localhost"
#define FOREMANCC_TEST_SCRIPT_POST_QUERY_PORT "8188"

#define FOREMANCC_TEST_SCRIPT_LOG_METHOD "test_log"
#define FOREMANCC_TEST_SCRIPT_LOG_LEVEL "debug"
#define FOREMANCC_TEST_SCRIPT_LOG_MESSAGE "test_message"

////////////////////////////////////////////////
// ManagerTestController.h
////////////////////////////////////////////////

namespace Foreman {
namespace Action {

  class ManagerTestController {
public:
    ManagerTestController();
    virtual ~ManagerTestController();

    void run(Manager* scriptMgr);

    bool testEcho(Manager* mgr, bool checkResultParameters = true);
    bool testRegister(Manager* mgr);
    bool testQuery(Manager* mgr);
    bool testLog(Manager* mgr);
  };
}
}

#endif
