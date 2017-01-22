// Copyright 2016-2017 Annotator Team

#define Annotator_AnnotatorLib_Attribute_BODY

/************************************************************
 Attribute class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Attribute.h"
#include <exception>
#include <sstream>
#include <stdexcept>

// Derived includes directives

namespace AnnotatorLib {

// static attributes (if any)
static unsigned long lastId = 100000;

Attribute::Attribute(std::shared_ptr<Attribute> &other)
    : Attribute(genId(), other->type, other->name) {
  this->value = Attribute::createAttributeValue(
      AttributeTypeToString(this->type), other->value->toString());
}

Attribute::Attribute(std::string type, std::string name)
    : Attribute(genId(), AttributeTypeFromString(type), name) {}

Attribute::Attribute(unsigned long id, AttributeType type, std::string name)
    : id(id) {
  if (lastId < id) lastId = id;
  this->type = type;
  this->name = name;
  this->value = createAttributeValue(type, "");
}

Attribute::~Attribute() {}

unsigned long Attribute::genId() {
  lastId += 7;
  return lastId;
}

std::shared_ptr<AttributeValue> Attribute::createAttributeValue(
    std::string type, std::string value) {
  AttributeType t = AttributeTypeFromString(type);
  return createAttributeValue(t, value);
}

std::shared_ptr<AttributeValue> Attribute::createAttributeValue(
    AttributeType type, std::string value) {
  switch (type) {
    case AnnotatorLib::AttributeType::STRING:
      return std::make_shared<AttributeValue>(value);
    case AnnotatorLib::AttributeType::INTEGER:
      return std::make_shared<AttributeValue>(std::stol(value));
    case AnnotatorLib::AttributeType::FLOAT:

      return std::make_shared<AttributeValue>(std::stod(value));
    case AnnotatorLib::AttributeType::BOOLEAN:
      if (value == "true" || value == "1" || value == "True" || value == "TRUE")
        return std::make_shared<AttributeValue>(true);
      else
        return std::make_shared<AttributeValue>(false);
    case AnnotatorLib::AttributeType::UNKNOWN:
      break;
    default:
      break;
  };
  return nullptr;
}

unsigned long Attribute::getId() const { return id; }

AttributeType Attribute::getType() const { return type; }

void Attribute::setName(std::string name) { this->name = name; }

std::string Attribute::getName() const { return name; }

void Attribute::setValue(std::shared_ptr<AttributeValue> value) {
  this->value = value;
}

std::shared_ptr<AttributeValue> Attribute::getValue() const { return value; }

bool Attribute::equals(Attribute *other) {
  if (this == other) return true;
  if (this->type != other->type) return false;
  if (this->name != other->name) return false;
  return true;
}

std::string AttributeValue::getString() {
  if (type != AnnotatorLib::AttributeType::STRING)
    throw std::invalid_argument("Attribute is not a String!");
  return stringValue;
}

long AttributeValue::getInteger() {
  if (type != AnnotatorLib::AttributeType::INTEGER)
    throw std::invalid_argument("Attribute is not an Integer!");
  return integerValue;
}

double AttributeValue::getFloat() {
  if (type != AnnotatorLib::AttributeType::FLOAT)
    throw std::invalid_argument("Attribute is not a Float!");
  return floatValue;
}

bool AttributeValue::getBoolean() {
  if (type != AnnotatorLib::AttributeType::BOOLEAN)
    throw std::invalid_argument("Attribute is not a Boolean!");
  return booleanValue;
}

void AttributeValue::setValue(std::string stringValue) {
  if (type != AnnotatorLib::AttributeType::STRING)
    throw std::invalid_argument("Attribute is not a String!");
  this->stringValue = stringValue;
}

void AttributeValue::setValue(long integerValue) {
  if (type != AnnotatorLib::AttributeType::INTEGER)
    throw std::invalid_argument("Attribute is not an Integer!");
  this->integerValue = integerValue;
}

void AttributeValue::setValue(double floatValue) {
  if (type != AnnotatorLib::AttributeType::FLOAT)
    throw std::invalid_argument("Attribute is not a Float!");
  this->floatValue = floatValue;
}

void AttributeValue::setValue(bool booleanValue) {
  if (type != AnnotatorLib::AttributeType::BOOLEAN)
    throw std::invalid_argument("Attribute is not a Boolean!");
  this->booleanValue = booleanValue;
}

std::string AttributeValue::toString() {
  std::string number;
  std::stringstream strstream;
  switch (type) {
    case AnnotatorLib::AttributeType::STRING:
      return stringValue;
    case AnnotatorLib::AttributeType::INTEGER:
      strstream << integerValue;
      strstream >> number;
      return number;
    case AnnotatorLib::AttributeType::FLOAT:
      strstream << floatValue;
      strstream >> number;
      return number;
    case AnnotatorLib::AttributeType::BOOLEAN:
      if (booleanValue)
        return "true";
      else
        return "false";
    case AnnotatorLib::AttributeType::UNKNOWN:
      break;
    default:
      break;
  };
  return "";
}

AttributeValue::AttributeValue(std::string stringValue) {
  this->type = AnnotatorLib::AttributeType::STRING;
  this->stringValue = stringValue;
}

AttributeValue::AttributeValue(const char *stringValue) {
  this->type = AnnotatorLib::AttributeType::STRING;
  this->stringValue = std::string(stringValue);
}

AttributeValue::AttributeValue(long integerValue) {
  this->type = AnnotatorLib::AttributeType::INTEGER;
  this->integerValue = integerValue;
}

AttributeValue::AttributeValue(int integerValue) {
  this->type = AnnotatorLib::AttributeType::INTEGER;
  this->integerValue = integerValue;
}

AttributeValue::AttributeValue(double floatValue) {
  this->type = AnnotatorLib::AttributeType::FLOAT;
  this->floatValue = floatValue;
}

AttributeValue::AttributeValue(float floatValue) {
  this->type = AnnotatorLib::AttributeType::FLOAT;
  this->floatValue = floatValue;
}

AttributeValue::AttributeValue(bool booleanValue) {
  this->type = AnnotatorLib::AttributeType::BOOLEAN;
  this->booleanValue = booleanValue;
}

AttributeType AttributeValue::getType() { return this->type; }

}  // of namespace AnnotatorLib

/************************************************************
 End of Attribute class body
 ************************************************************/
