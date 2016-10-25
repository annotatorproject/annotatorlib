// Copyright 2016 Annotator Team
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/NewAnnotation.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::NewAnnotation::NewAnnotation(
    const unsigned long newObjectId, const shared_ptr<Class> newObjectClass,
    std::shared_ptr<Session> session, shared_ptr<Frame> frame, float x, float y,
    float width, float height, float confidence)
    : newObjectId(newObjectId),
      newObjectClass(newObjectClass),
      createNewObject(true) {
  this->session = session;
  this->frame = frame;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->confidence = confidence;
}

AnnotatorLib::Commands::NewAnnotation::NewAnnotation(
    std::shared_ptr<Session> session, shared_ptr<Object> object,
    shared_ptr<Frame> frame, float x, float y, float width, float height,
    float confidence)
    : newObjectId(0), newObjectClass(0), createNewObject(false) {
  this->session = session;
  this->object = object;
  this->frame = frame;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->confidence = confidence;
}

bool AnnotatorLib::Commands::NewAnnotation::execute() {
  if (createNewObject)
    object = std::make_shared<Object>(newObjectId, newObjectClass);

  this->annotation_ = Annotation::make_shared(frame, object);
  this->annotation_->setPosition(x, y, width, height);
  this->annotation_->setConfidenceScore(confidence);
  bool success = session->addAnnotation(
      annotation_, true);  // adds annotation and register to them
  if (createNewObject && success) createdNewObject = true;
  return success;
}

bool AnnotatorLib::Commands::NewAnnotation::undo() {
  this->annotation_ = session->removeAnnotation(
      annotation_->getId(),
      true);  // remove annotation from session and unregister
  // remove frame and object if empty
  if (!this->annotation_->getObject()->hasAnnotations())
    session->removeObject(this->annotation_->getObject()->getId(), false);
  if (!this->annotation_->getObject()->hasAnnotations())
    session->removeFrame(this->annotation_->getFrame()->getId(), false);
  return !this->annotation_;
}

shared_ptr<AnnotatorLib::Annotation>
AnnotatorLib::Commands::NewAnnotation::getAnnotation() {
  return annotation_;
}
