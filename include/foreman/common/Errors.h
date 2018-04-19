/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ERROR_NO_H_
#define _FOREMANCC_ERROR_NO_H_

namespace Foreman {

const static int ERROR_UNKNOWN = 0;
const static int ERROR_BAD_DESTINATION = 300;
const static int ERROR_INVALID_REQUEST = 400;
const static int ERROR_METHOD_NOT_FOUND = 401;
const static int ERROR_INVALID_PARAMS = 402;
const static int ERROR_INTERNAL_ERROR = 600;
const static int ERROR_SCRIPT_ENGINE_INTERNAL_ERROR = 700;
const static int ERROR_SCRIPT_ENGINE_NOT_FOUND = 701;
const static int ERROR_SCRIPT_COMPILE_ERROR = 702;
const static int ERROR_SCRIPT_RUNTIME_ERROR = 703;

inline const char* ErrorCodeToMessage(int code)
{
  switch (code) {
  case 0:
    return "Unknown Error";
  case 300:
    return "Bad Destination";
  case 400:
    return "Invalid Request";
  case 401:
    return "Method not found";
  case 402:
    return "Invalid params";
  case 600:
    return "Internal error";
  case 700:
    return "Script Engine Internal Error";
  case 701:
    return "Script Engine Not Found";
  case 702:
    return "Script Compile Error";
  case 703:
    return "Script Runtime Error";
  }
  return "";
}
}

#endif
