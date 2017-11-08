/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ERROR_H_
#define _FOREMANCC_ERROR_H_

#include <string>
#include <errno.h>

namespace Foreman {

class Error {

  public:
  Error();
  Error(int code);
  Error(int code, const std::string& message);
  Error(int code, const std::string& message, int detailCode, const std::string& detailMessage);

  virtual ~Error();

  bool isError();

  void setCode(int value)
  {
    this->code = value;
  }

  void setMessage(const std::string& value)
  {
    this->message = value;
  }

  int getCode() const
  {
    return this->code;
  }

  const char* getMessage() const
  {
    return this->message.c_str();
  }

  void setDetailCode(int value)
  {
    this->detailCode = value;
  }

  void setDetailMessage(const std::string& value)
  {
    this->detailMessage = value;
  }

  int getDetailCode() const
  {
    return this->detailCode;
  }

  const char* getDetailMessage() const
  {
    return this->detailMessage.c_str();
  }

  bool equals(const Error& err) const;

  void setErrorNo(int errno);

private:
  void initialize();

  int code;
  std::string message;

  int detailCode;
  std::string detailMessage;
};
}

#endif
