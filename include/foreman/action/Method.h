/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ACTION_METHOD_H_
#define _FOREMANCC_ACTION_METHOD_H_

#include <map>
#include <string>

#include <foreman/Platform.h>
#include <foreman/action/Parameter.h>
#include <foreman/common/Error.h>
#include <foreman/util/Mutex.h>

namespace Foreman {
namespace Action {

  ////////////////////////////////////////////////
  // Method
  ////////////////////////////////////////////////

  class Method {
public:
    static Method* CreateMethod(const std::string& lang);

public:
    Method();
    Method(const std::string& lang);

    virtual ~Method();

    const std::string& getLanguage() const
    {
      return this->language;
    }

    bool setLanguage(const std::string& lang)
    {
      this->language = lang;
      return true;
    }

    const std::string& getLanguage()
    {
      return this->language;
    }

    bool isLanguage(const std::string& lang) const
    {
      return (this->language.compare(lang) == 0) ? true : false;
    }

    bool setName(const std::string& name)
    {
      this->name = name;
      return true;
    }

    const std::string& getName() const
    {
      return this->name;
    }

    const bool hasName() const
    {
      return (0 < this->name.length()) ? true : false;
    }

    bool setCode(const byte* code, size_t codeLen);
    bool setCode(const std::string code);

    bool isBinaryCode();

    const byte* getCode() const
    {
      return this->code;
    }

    const char* getStringCode() const
    {
      return (const char*)this->code;
    }

    size_t getCodeLength() const
    {
      return this->codeLen;
    }

    const bool hasCode() const
    {
      return (0 < this->codeLen) ? true : false;
    }

private:
    void init();

private:
    std::string language;
    std::string name;
    byte* code;
    size_t codeLen;
  };

  ////////////////////////////////////////////////
  // MethodMap
  ////////////////////////////////////////////////

  class MethodMap : public std::map<std::string, Method*> {

public:
    MethodMap();
    virtual ~MethodMap();

    bool hasMethod(const std::string& name) const;
    Method* getMethod(const std::string& name);

    void clear();
  };

  enum MethodEngineStatus {
    MethodEngineStatusOk = 200,
    MethodEngineStatusBadRequest = 400,
  };
}
}

#endif
