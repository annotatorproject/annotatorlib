// Copyright 2016 Annotator Team
#ifndef NEWATTRIBUTE_H
#define NEWATTRIBUTE_H

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

class ANNOTATORLIB_API NewAttribute : public Command {
public:
  NewAttribute() = delete;

  NewAttribute(std::shared_ptr<Session> session, shared_ptr<Object> object,
               std::string type, std::string name, std::string value);

  NewAttribute(const NewAttribute &other) = delete;

  ~NewAttribute() {}

  virtual bool execute(Session *informSession = 0) override;

  virtual bool undo(Session *informSession = 0) override;

  shared_ptr<Attribute> getAttribute();

protected:
  shared_ptr<Attribute> attribute_;
  const std::shared_ptr<AnnotatorLib::Session> session;
  const shared_ptr<AnnotatorLib::Object> object;
  std::string type;
  std::string name;
  std::string value;
};
}
}
#endif // NEWANNOTATION_H
