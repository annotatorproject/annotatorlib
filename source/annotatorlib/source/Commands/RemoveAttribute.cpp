// Copyright 2016-2017 Annotator Team

#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Attribute.h>
#include <AnnotatorLib/Commands/RemoveAttribute.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

#include <exception>

AnnotatorLib::Commands::RemoveAttribute::RemoveAttribute(
    std::shared_ptr<AnnotatorLib::Session> session,
    shared_ptr<AnnotatorLib::Object> object, std::string name)
    : session(session), object(object) {
  this->attribute_ = object->getAttribute(name);
}

AnnotatorLib::Commands::RemoveAttribute::RemoveAttribute(
    std::shared_ptr<AnnotatorLib::Session> session,
    shared_ptr<AnnotatorLib::Object> object,
    std::shared_ptr<AnnotatorLib::Attribute> attribute)
    : session(session), object(object) {
  this->attribute_ = attribute;
}

bool AnnotatorLib::Commands::RemoveAttribute::execute(
    AnnotatorLib::Session *informSession) {
  if (object) {
    object->removeAttribute(attribute_);
    // TODO also remove attributes from annotations
  } else {
    throw std::runtime_error(
        "No object or annotation given to NewAttribute Command.");
  }
  if (informSession) {
    informSession->updateObject(object);
  }
  return true;
}

bool AnnotatorLib::Commands::RemoveAttribute::undo(
    AnnotatorLib::Session *informSession) {
  object->addAttribute(attribute_);

  if (informSession) {
    informSession->updateObject(object);
  }
  return true;
}

shared_ptr<AnnotatorLib::Attribute>
AnnotatorLib::Commands::RemoveAttribute::getAttribute() {
  return attribute_;
}
