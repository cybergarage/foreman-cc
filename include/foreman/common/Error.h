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
#include <iostream>

#include <foreman/common/Errors.h>

namespace Foreman {

#ifdef DEBUG
#define FOREMANCC_ERROR_SET_ERRORNO(err, errcode) \
  {                                               \
    err->setFileName(__FILE__);                   \
    err->setLineNo(__LINE__);                     \
    err->setFuncName(__PRETTY_FUNCTION__);        \
    err->setErrorNo(errcode);                     \
  }
#else
#define FOREMANCC_ERROR_SET_ERRORNO(err, errcode) \
  {                                               \
    err->setErrorNo(errcode);                     \
  }
#endif

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

  void setDetailCode(int value)
  {
    this->detailCode = value;
  }

  void setDetailMessage(const std::string& value)
  {
    this->detailMessage = value;
  }

  void setLineNo(int value)
  {
    this->lineNo = value;
  }

  void setFileName(const std::string& value)
  {
    this->fileName = value;
  }

  void setFuncName(const std::string& value)
  {
    this->funcName = value;
  }

  int getCode() const
  {
    return this->code;
  }

  bool hasCode() const
  {
    return (0 < this->code) ? true : false;
  }

  bool isInternalError() const
  {
    if (this->code < ERROR_INTERNAL_ERROR)
      return false;
    return true;
  }

  const std::string &getMessage() const
  {
    return this->message;
  }

  bool hasMessage() const
  {
    return (0 < this->message.length()) ? true : false;
  }

  int getDetailCode() const
  {
    return this->detailCode;
  }

  bool hasDetailCode() const
  {
    return (0 < this->detailCode) ? true : false;
  }

  const std::string &getDetailMessage() const
  {
    return this->detailMessage;
  }

  bool hasDetailMessage() const
  {
    return (0 < this->detailMessage.length()) ? true : false;
  }

  int getLineNo() const
  {
    return this->lineNo;
  }

  const char* getFileName() const
  {
    return this->fileName.c_str();
  }

  const char* getFuncName() const
  {
    return this->funcName.c_str();
  }

  bool equals(const Error& err) const;

  void setErrorNo(int errorno);

  friend std::ostream& operator<<(std::ostream&, const Error&);
  
  private:
  void initialize();

  int code;
  std::string message;

  int detailCode;
  std::string detailMessage;

  int lineNo;
  std::string fileName;
  std::string funcName;
};


std::ostream& operator<<(std::ostream&, const Error&);

}

#endif
