#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/NewAnnotation.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::NewAnnotation::NewAnnotation(
    const unsigned long newObjectId,
    const shared_ptr<Class> newObjectClass,
    AnnotatorLib::Session *session,
    shared_ptr<Frame> frame,
    float x,
    float y,
    float width,
    float height ) : createNewObject(true) {

  this->session = session;
  this->annotation_ = Annotation::make_shared(frame, std::make_shared<Object>(newObjectId, newObjectClass));
  this->annotation_->setPosition(x, y, width, height);
}

AnnotatorLib::Commands::NewAnnotation::NewAnnotation(
    AnnotatorLib::Session *session,
    shared_ptr<Object> object,
    shared_ptr<Frame> frame,
    float x, float y, float width, float height) : createNewObject(false) {

  this->session = session;
  this->annotation_ = Annotation::make_shared(frame, object);
  this->annotation_->setPosition(x, y, width, height);
}

bool AnnotatorLib::Commands::NewAnnotation::execute() {
  bool success = session->addAnnotation(annotation_, true);  // adds annotation and register to them
  if (createNewObject && success)
    createdNewObject = true;
}

bool AnnotatorLib::Commands::NewAnnotation::undo() {
  this->annotation_ = session->removeAnnotation(annotation_->getId(), true);  // remove annotation from session and unregister
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
