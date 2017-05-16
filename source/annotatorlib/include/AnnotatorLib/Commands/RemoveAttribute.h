// Copyright 2016-2017 Annotator Team

#ifndef REMOVEATTRIBUTE_H
#define REMOVEATTRIBUTE_H

#include <AnnotatorLib/Commands/Command.h>
#include <memory>
#include <string>

using std::shared_ptr;

namespace AnnotatorLib {

class Object;
class Session;
class Attribute;
class Frame;

namespace Commands {

class ANNOTATORLIB_API RemoveAttribute : public Command {
 public:
  RemoveAttribute() = delete;

  RemoveAttribute(std::shared_ptr<Session> session, shared_ptr<Object> object,
                  std::string name);

  RemoveAttribute(std::shared_ptr<Session> session,
                  shared_ptr<AnnotatorLib::Object> object,
                  std::shared_ptr<Attribute> attribute);

  RemoveAttribute(std::shared_ptr<Session> session,
                  shared_ptr<AnnotatorLib::Frame> frame,
                  std::shared_ptr<Attribute> attribute);

  virtual bool execute(Session *informSession = 0) override;

  virtual bool undo(Session *informSession = 0) override;

  shared_ptr<Attribute> getAttribute();

 protected:
  shared_ptr<Attribute> attribute_;
  const std::shared_ptr<AnnotatorLib::Session> session;
  const shared_ptr<AnnotatorLib::Object> object;
  const shared_ptr<AnnotatorLib::Frame> frame;
};
}
}
#endif  // REMOVEATTRIBUTE_H
