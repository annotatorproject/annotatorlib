// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_ATTRIBUTE_H
#define ANNOTATOR_ANNOTATORLIB_ATTRIBUTE_H

/************************************************************
 Attribute class header
 ************************************************************/
#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>

namespace AnnotatorLib {

/************************************************************/

/**
 * @brief The AttributeValue class
 */
class ANNOTATORLIB_API AttributeValue {
 public:
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
 */
class ANNOTATORLIB_API Attribute {
 public:
  const unsigned long id;

  Attribute(unsigned long id, AttributeType type, std::string name);

  ~Attribute() {}

  /**
   *
   * @return id
   */
  static unsigned long genId();

  unsigned long getId() const;

  AttributeType getType() const;

  void setName(std::string name);
  std::string getName() const;

  void setDefaultValue(AttributeValue *value);
  AttributeValue *getDefaultValue() const;

  bool equals(Attribute *other);

 protected:
  /**
   *
   */
  AttributeType type;

  std::string name;

  AttributeValue *defaultValue;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of Attribute class header
 ************************************************************/

#endif
