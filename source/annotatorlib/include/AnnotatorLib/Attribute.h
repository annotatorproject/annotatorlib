// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_ATTRIBUTE_H
#define ANNOTATOR_ANNOTATORLIB_ATTRIBUTE_H

/************************************************************
 Attribute class header
 ************************************************************/
#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <map>
#include <memory>

namespace AnnotatorLib {

/************************************************************/

/**
 * @brief The AttributeValue class
 */
class ANNOTATORLIB_API AttributeValue {
 public:
  // AttributeValue() = delete;
  AttributeValue(std::string stringValue);
  AttributeValue(const char *stringValue);
  AttributeValue(long integerValue);
  AttributeValue(int integerValue);
  AttributeValue(double floatValue);
  AttributeValue(float floatValue);
  AttributeValue(bool booleanValue);

  AttributeType getType();

  std::string getString();
  long getInteger();
  double getFloat();
  bool getBoolean();

  void setValue(std::string stringValue);
  void setValue(long integerValue);
  void setValue(double floatValue);
  void setValue(bool booleanValue);

  std::string toString();

 protected:
  AttributeType type;
  std::string stringValue = "";
  long integerValue;
  double floatValue;
  bool booleanValue;
};

/**
 * @brief The Attribute class
 * Attribute at object is used as default attribute value.
 */
class ANNOTATORLIB_API Attribute {
 public:
  const unsigned long id;

  Attribute(std::shared_ptr<Attribute> &other);

  Attribute(std::string type, std::string name);

  Attribute(unsigned long id, AttributeType type, std::string name);

  ~Attribute();

  /**
   *
   * @return id
   */
  static unsigned long genId();

  static std::shared_ptr<AttributeValue> createAttributeValue(
      std::string type, std::string value);

  static std::shared_ptr<AttributeValue> createAttributeValue(
      AttributeType type, std::string value);

  unsigned long getId() const;

  AttributeType getType() const;

  void setName(std::string name);
  std::string getName() const;

  void setValue(std::shared_ptr<AttributeValue> value);
  std::shared_ptr<AttributeValue> getValue() const;

  bool equals(Attribute *other);

 protected:
  /**
   *
   */
  AttributeType type;

  std::string name;

  std::shared_ptr<AttributeValue> value;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/
typedef std::map<unsigned long, std::shared_ptr<Attribute>> AttributeMap;

}  // of namespace AnnotatorLib

/************************************************************
 End of Attribute class header
 ************************************************************/

#endif
