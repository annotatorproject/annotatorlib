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

AnnotatorLib::Commands::RemoveAttribute::RemoveAttribute(
    std::shared_ptr<AnnotatorLib::Session> session,
    shared_ptr<AnnotatorLib::Frame> frame,
    std::shared_ptr<AnnotatorLib::Attribute> attribute)
    : session(session), frame(frame) {
  this->attribute_ = attribute;
}

bool AnnotatorLib::Commands::RemoveAttribute::execute(
    AnnotatorLib::Session *informSession) {
  if (object) {
    object->removeAttribute(attribute_);
    // TODO also remove attributes from annotations
  } else if (frame) {
    frame->removeAttribute(attribute_);
  } else {
    throw std::runtime_error(
        "No frame, object or annotation given to RemoveAttribute Command.");
  }
  if (informSession) {
    informSession->updateObject(object);
  }
  return true;
}

bool AnnotatorLib::Commands::RemoveAttribute::undo(
    AnnotatorLib::Session *informSession) {
  if (object) {
    if (informSession) {
      informSession->updateObject(object);
    }
    object->addAttribute(attribute_);
  } else if (frame) {
    frame->addAttribute(attribute_);
    informSession->updateFrame(frame);
  }

  return true;
}

shared_ptr<AnnotatorLib::Attribute>
AnnotatorLib::Commands::RemoveAttribute::getAttribute() {
  return attribute_;
}
