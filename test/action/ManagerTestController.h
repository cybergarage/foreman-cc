/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_SCRIPT_MANAGERTESTCONTROLLER_H_
#define _FOREMANCC_SCRIPT_MANAGERTESTCONTROLLER_H_

#include <foreman/action/Manager.h>

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

#define FOREMANCC_SCRIPT_ECHO_METHOD "test_echo"
#define FOREMANCC_SCRIPT_ECHO_PARAM_NAME "message"
#define FOREMANCC_SCRIPT_ECHO_PARAM_VALUE "echo"

#define FOREMANCC_SCRIPT_SET_REGISTER_METHOD "test_setregister"
#define FOREMANCC_SCRIPT_SET_REGISTER_METHOD_PARAM_NAME "test_message"
#define FOREMANCC_SCRIPT_SET_REGISTER_METHOD_PARAM_VALUE "echo"

#define FOREMANCC_SCRIPT_GET_REGISTER_METHOD "test_getregister"
#define FOREMANCC_SCRIPT_GET_REGISTER_METHOD_PARAM_NAME FOREMANCC_SCRIPT_POST_REGISTER_METHOD_PARAM_NAME
#define FOREMANCC_SCRIPT_GET_REGISTER_METHOD_PARAM_VALUE FOREMANCC_SCRIPT_POST_REGISTER_METHOD_PARAM_VALUE

#define FOREMANCC_SCRIPT_REMOVE_REGISTER_METHOD "test_removeregister"
#define FOREMANCC_SCRIPT_REMOVE_REGISTER_METHOD_PARAM_NAME FOREMANCC_SCRIPT_POST_REGISTER_METHOD_PARAM_NAME

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

    void testEcho(Manager* mgr, bool checkResultParameters = true);
    void testRegister(Manager* mgr);
  };
}
}

#endif
