/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ACTION_DEFAULT_H_
#define _FOREMANCC_ACTION_DEFAULT_H_

#include <foreman/action/Script.h>

namespace Foreman {
namespace Action {

  ////////////////////////////////////////////////
  // LuaEngine
  ////////////////////////////////////////////////

  class DefaultScriptManager : public ScriptManager {

public:
    DefaultScriptManager();
  };
}
}

#endif
