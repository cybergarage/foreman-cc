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

#define FOREMANCC_SCRIPT_HELLO_ECHO_METHOD "echo"
#define FOREMANCC_SCRIPT_HELLO_ECHO_PARAM_NAME "message"
#define FOREMANCC_SCRIPT_HELLO_ECHO_PARAM_VALUE "hello"

////////////////////////////////////////////////
// ScriptManagerTestController
////////////////////////////////////////////////

namespace Foreman {
namespace Action {

  class ScriptManagerTestController {
public:
    ScriptManagerTestController();
    virtual ~ScriptManagerTestController();

    void run(ScriptManager* scriptMgr);

private:
    void testHello(ScriptManager* scriptMgr);
  };
}
}

#endif
