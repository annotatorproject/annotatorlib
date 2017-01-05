// Copyright 2016-2017 Annotator Team

#include <exception>

#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Attribute.h>
#include <AnnotatorLib/Commands/NewAttribute.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::NewAttribute::NewAttribute(
    std::shared_ptr<AnnotatorLib::Session> session,
    shared_ptr<AnnotatorLib::Object> object, std::string type, std::string name,
    std::string value)
    : session(session), object(object), type(type), name(name), value(value) {
  attribute_ = std::make_shared<AnnotatorLib::Attribute>(type, name);
  std::shared_ptr<AnnotatorLib::AttributeValue> av =
      AnnotatorLib::Attribute::createAttributeValue(type, value);
  attribute_->setValue(av);
}

AnnotatorLib::Commands::NewAttribute::NewAttribute(
    std::shared_ptr<AnnotatorLib::Session> session,
    shared_ptr<AnnotatorLib::Object> object,
    std::shared_ptr<AnnotatorLib::Attribute> attribute)
    : session(session), object(object) {
  attribute_ = attribute;
}

AnnotatorLib::Commands::NewAttribute::NewAttribute(
    std::shared_ptr<AnnotatorLib::Session> session,
    shared_ptr<AnnotatorLib::Annotation> annotation,
    std::shared_ptr<AnnotatorLib::Attribute> attribute)
    : session(session), annotation(annotation) {
  attribute_ = attribute;
}

bool AnnotatorLib::Commands::NewAttribute::execute(
    AnnotatorLib::Session *informSession) {
  if (object)
    object->addAttribute(attribute_);
  else if (annotation) {
    annotation->addAttribute(attribute_);
    if (!annotation->getObject()->getAttribute(attribute_->getName())) {
      annotation->getObject()->addAttribute(
          std::make_shared<Attribute>(attribute_));
    }
  } else {
    throw std::runtime_error(
        "No object or annotation given to NewAttribute Command.");
  }
  if (informSession) {
    if (this->object) informSession->updateObject(this->object);
    if (this->annotation) {
      informSession->updateAnnotation(this->annotation);
      informSession->updateObject(this->annotation->getObject());
    }
  }
  return true;
}

bool AnnotatorLib::Commands::NewAttribute::undo(
    AnnotatorLib::Session *informSession) {
  // TODO
}

shared_ptr<AnnotatorLib::Attribute>
AnnotatorLib::Commands::NewAttribute::getAttribute() {
  return attribute_;
}
