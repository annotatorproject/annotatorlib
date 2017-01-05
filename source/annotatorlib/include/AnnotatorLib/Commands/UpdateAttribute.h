// Copyright 2016-2017 Annotator Team
#ifndef UPDATEATTRIBUTE_H
#define UPDATEATTRIBUTE_H

#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Attribute.h>
#include <AnnotatorLib/Commands/Command.h>
#include <memory>
#include <string>

using std::shared_ptr;

namespace AnnotatorLib {

class Object;
class Class;
class Session;
class Annotation;
class Attribute;
class Frame;

namespace Commands {

class ANNOTATORLIB_API UpdateAttribute : public Command {
 public:
  UpdateAttribute(shared_ptr<Annotation> annotation, std::string name,
                  std::string value);

  UpdateAttribute(const UpdateAttribute &other) = delete;

  ~UpdateAttribute() {}

  virtual bool execute(Session *informSession = 0) override;

  virtual bool undo(Session *informSession = 0) override;

  shared_ptr<Attribute> getAttribute();

 protected:
  const std::shared_ptr<AnnotatorLib::Session> session;
  const shared_ptr<AnnotatorLib::Annotation> annotation;
  std::string type;
  std::string name;
  std::string value;

  std::shared_ptr<AnnotatorLib::AttributeValue> oldValue;
  bool wasDefault = false;
};
}
}
#endif  // UPDATEATTRIBUTE_H
