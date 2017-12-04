/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ACTION_PARAMETER_H_
#define _FOREMANCC_ACTION_PARAMETER_H_

#include <memory>
#include <string>
#include <vector>

#include <foreman/Platform.h>

namespace Foreman {
namespace Action {

  ////////////////////////////////////////////////
  // Type
  ////////////////////////////////////////////////

   enum ParameterType { IntegerType, RealType, StringType, BoolType };
  
  ////////////////////////////////////////////////
  // Parameter
  ////////////////////////////////////////////////

  class Parameter {
public:
    Parameter(ParameterType type);
    virtual ~Parameter();

    void setName(const std::string& name)
    {
      name_ = name;
    }

    const char* getName()
    {
      return name_.c_str();
    }

    bool isInterger() {return isType(IntegerType);}
    bool isReal() {return isType(RealType);}
    bool isString() {return isType(StringType);}
    bool isBool() {return isType(BoolType);}

  private:
    bool isType(ParameterType type) {
      return (type_ == type) ? true : false;
    }

  protected:
    std::string name_;
    ParameterType type_;
    
  };
  
  class Integer : public Parameter {
  public:
    Integer() : Parameter(IntegerType) {}
    ~Integer() {}
    void setValue(int value) {value_ = value;}
    int getValue() {return value_;}
  private:
    int value_;
  };

  class Real : public Parameter {
  public:
    Real() : Parameter(RealType) {}
    ~Real() {}
    void setValue(double value) {value_ = value;}
    double getValue() {return value_;}
  private:
    double value_;
  };

  class String : public Parameter {
  public:
    String() : Parameter(StringType) {}
    ~String() {}
    void setValue(const std::string &value) {value_ = value;}
    const std::string &getValue() {return value_;}
  private:
    std::string value_;
  };

  class Bool : public Parameter {
  public:
    Bool() : Parameter(BoolType) {}
    ~Bool() {}
    void setValue(bool value) {value_ = value;}
    bool getValue() {return value_;}
  private:
    bool value_;
  };
  
  ////////////////////////////////////////////////
  // Parameters
  ////////////////////////////////////////////////

  class Parameters : public std::vector<std::shared_ptr<Parameter>> {
public:
    Parameters();
    virtual ~Parameters();

    bool addParameter(Parameter* param);
    bool addParameter(const Parameter& param);
    bool addParameter(std::shared_ptr<Parameter> param);

    Parameter* getParameter(size_t n);
  };
}
}

#endif
