/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <iostream>
#include <sstream>
#include <string>

#include <foreman/registry/Object.h>

using namespace Foreman::Registry;

////////////////////////////////////////////////
// Object
////////////////////////////////////////////////

Object::Object()
{
  clear();
}

Object::~Object()
{
  clear();
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool Object::clear()
{
  this->objId = "";
  this->parentId = "";
  this->name = "";
  this->data = "";
  this->propData = "";

  return true;
}

////////////////////////////////////////////////
// setProperty
////////////////////////////////////////////////

bool Object::setProperty(Property* prop)
{
  Properties props;
  if (!getProperties(&props))
    return false;

  if (!props.setProperty(prop))
    return false;

  if (!updatePropertyData(&props))
    return false;

  return true;
}

////////////////////////////////////////////////
// getProperty
////////////////////////////////////////////////

bool Object::getProperty(const std::string& name, Property* prop)
{
  Properties props;
  if (!getProperties(&props))
    return false;

  Property* foundProp = props.getProperty(name);
  if (foundProp)
    return false;

  return true;
}

////////////////////////////////////////////////
// getProperties
////////////////////////////////////////////////

bool Object::getProperties(Properties* props)
{
  std::istringstream propsStream(this->propData);

  std::string propLine;
  std::vector<std::string> propLines;
  while (std::getline(propsStream, propLine, (char)FOREMANCC_REGISTRY_PROPERTIES_DELIM)) {
    propLines.push_back(propLine);
  }

  for (auto propLine : propLines) {
    size_t propDelimIdx = propLine.find((char)FOREMANCC_REGISTRY_PROPERTY_DELIM);
    if (propDelimIdx == std::string::npos)
      return false;
    std::string name = propLine.substr(0,propDelimIdx);
    std::string value = propLine.substr((propDelimIdx+1));
    
    Property *prop = new Property();
    if (!prop)
      return false;
    prop->setName(name);
    prop->setData(value);
    props->addProperty(prop);
  }
  
  return true;
}

////////////////////////////////////////////////
// updatePropertyData
////////////////////////////////////////////////

bool Object::updatePropertyData(Properties* props)
{
  std::stringstream propDataStream;
  
  bool firstProperty = true;
  for (auto prop : *props) {
    if (!firstProperty) {
      propDataStream << (char)FOREMANCC_REGISTRY_PROPERTIES_DELIM;
    }
    else {
      firstProperty = false;
    }
    
    propDataStream << prop->getName();
    propDataStream << (char)FOREMANCC_REGISTRY_PROPERTY_DELIM;
    propDataStream << prop->getData();
  }
  
  setPropertyData(propDataStream.str());
  
  return true;
}

////////////////////////////////////////////////
// equals
////////////////////////////////////////////////

bool Object::equals(Object* obj) const
{
  if (this->objId.compare(obj->getId()) != 0)
    return false;

  if (this->parentId.compare(obj->getParentId()) != 0)
    return false;

  if (this->name.compare(obj->getName()) != 0)
    return false;

  if (this->data.compare(obj->getData()) != 0)
    return false;

  if (this->propData.compare(obj->getPropertyData()) != 0)
    return false;
  
  return true;
}
