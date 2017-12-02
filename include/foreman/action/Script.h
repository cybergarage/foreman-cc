/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ACTION_SCRIPT_H_
#define _FOREMANCC_ACTION_SCRIPT_H_

#include <map>
#include <string>

#include <foreman/Platform.h>
#include <foreman/action/Parameter.h>
#include <foreman/common/Error.h>
#include <foreman/util/Mutex.h>

namespace Foreman {
namespace Action {

  ////////////////////////////////////////////////
  // Script
  ////////////////////////////////////////////////
  
  class Script {
public:
    static const int ENCODING_NONE;
    static const int ENCODING_BASE64;

public:
    static Script* CreateScript(const std::string& lang);

public:
    Script(const std::string& lang);

    virtual ~Script();

    const std::string& getLanguage() const
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

    const char* getName() const
    {
      return this->name.c_str();
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

    bool setEncording(int encoding)
    {
      this->codeEncoding = encoding;
      return true;
    }

    const bool hasEncording() const
    {
      return (0 < this->codeEncoding) ? true : false;
    }

    int getEncording() const
    {
      return this->codeEncoding;
    }

    bool isEncoding(int encoding) const
    {
      return (this->codeEncoding == encoding) ? true : false;
    }

    bool isBase64Encoded() const
    {
      return isEncoding(ENCODING_BASE64);
    }

    bool isEncoded() const
    {
      return !isEncoding(ENCODING_NONE);
    }

private:
    void init();

private:
    std::string language;
    std::string name;
    byte* code;
    size_t codeLen;
    int codeEncoding;
  };

  ////////////////////////////////////////////////
  // ScriptMap
  ////////////////////////////////////////////////
  
  class ScriptMap : public std::map<std::string, Script*> {

public:
    ScriptMap();
    virtual ~ScriptMap();

    bool hasScript(const std::string& name) const;
    Script* getScript(const std::string& name);

    void clear();
  };

  enum ScriptEngineStatus {
    ScriptEngineStatusOk = 200,
    ScriptEngineStatusBadRequest = 400,
  };

  ////////////////////////////////////////////////
  // ScriptEngine
  ////////////////////////////////////////////////
  
  class ScriptEngine {

public:
    ScriptEngine(const std::string& lang);
    virtual ~ScriptEngine();

    const std::string& getLanguage() const
    {
      return this->language;
    }

    virtual bool compile(Script* script, Error* error) = 0;
    virtual bool run(const Script* script, const Parameters* params, Parameters* results, Error* error) const = 0;

    void lock() const
    {
      mutex.lock();
    }

    void unlock() const
    {
      mutex.unlock();
    }

private:
    void init();

private:
    std::string language;
    mutable Mutex mutex;
  };

  ////////////////////////////////////////////////
  // ScriptEngineMap
  ////////////////////////////////////////////////
  
  class ScriptEngineMap : public std::map<std::string, ScriptEngine*> {

public:
    ScriptEngineMap();
    virtual ~ScriptEngineMap();

    bool hasEngine(const std::string& lang) const;
    ScriptEngine* getEngine(const std::string& lang);

    void clear();

private:
    void init();
  };

  ////////////////////////////////////////////////
  // ScriptManager
  ////////////////////////////////////////////////
  
  class ScriptManager {

public:
    ScriptManager();
    virtual ~ScriptManager();

    bool setScript(const std::string& method, const std::string& lang, const std::string& script, int encodeType, Error* error);
    bool setScript(Script* script);

    bool hasScript(const std::string& name) const
    {
      return this->scripts.hasScript(name);
    }

    bool removeScript(const std::string& method, Error* error);

    bool setEngine(ScriptEngine* engine);

    bool hasEngine(const std::string& lang) const
    {
      return this->engines.hasEngine(lang);
    }

    bool execMethod(const std::string& name, const Parameters* params, Parameters* results, Error* error);

private:
    ScriptMap scripts;
    ScriptEngineMap engines;
  };
}
}

#endif
