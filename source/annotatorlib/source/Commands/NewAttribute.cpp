// Copyright 2016 Annotator Team
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Attribute.h>
#include <AnnotatorLib/Commands/NewAttribute.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>


AnnotatorLib::Commands::NewAttribute::NewAttribute(std::shared_ptr<AnnotatorLib::Session> session, shared_ptr<AnnotatorLib::Object> object, std::string type, std::string name, std::string value): session(session),
    object(object), type(type), name(name), value(value)
{

}

bool AnnotatorLib::Commands::NewAttribute::execute(AnnotatorLib::Session *informSession)
{
    attribute_ = std::make_shared<AnnotatorLib::Attribute>(type, name);
    AnnotatorLib::AttributeValue *av = AnnotatorLib::Attribute::createAttributeValue(type, value);
    attribute_->setValue(av);
    object->addAttribute(attribute_);
    if (informSession) {
      informSession->updateObject(this->object);
    }
    return true;
}

bool AnnotatorLib::Commands::NewAttribute::undo(AnnotatorLib::Session *informSession)
{
// TODO
}

shared_ptr<AnnotatorLib::Attribute> AnnotatorLib::Commands::NewAttribute::getAttribute()
{
 return attribute_;
}
/*
bool AnnotatorLib::Commands::NewAnnotation::execute(
    AnnotatorLib::Session *informSession) {

    attribute_ = std::make_shared<AnnotatorLib::Attribute>()

  if (createNewObject)
    object = std::make_shared<Object>(newObjectId, newObjectClass);

  this->annotation_ = Annotation::make_shared(frame, object);
  this->annotation_->setPosition(x, y, width, height);
  this->annotation_->setConfidenceScore(confidence);
  bool success = session->addAnnotation(
      annotation_, true);  // adds annotation and register to them
  if (createNewObject && success) createdNewObject = true;
  if (informSession) {
    informSession->updateAnnotation(this->annotation_);
  }
  return success;
}

bool AnnotatorLib::Commands::NewAnnotation::undo(
    AnnotatorLib::Session *informSession) {
  this->annotation_ = session->removeAnnotation(
      annotation_->getId(),
      true);  // remove annotation from session and unregister
  // remove frame and object if empty
  if (!this->annotation_->getObject()->hasAnnotations())
    session->removeObject(this->annotation_->getObject()->getId(), false);
  if (!this->annotation_->getObject()->hasAnnotations())
    session->removeFrame(this->annotation_->getFrame()->getId(), false);
  bool ret = !this->annotation_;
  if (informSession) {
    informSession->updateAnnotation(this->annotation_);
  }
  return ret;
}
*/


