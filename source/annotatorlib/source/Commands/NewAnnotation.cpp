#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/NewAnnotation.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::NewAnnotation::NewAnnotation(
    unsigned long newObjectId, Class* newObjectClass, AnnotatorLib::Frame *frame, float x, float y,
    float width, float height, AnnotatorLib::Session *session,
    bool isLast = false) {
  this->createNewObject = true;
  this->newObjectId = newObjectId;
  this->newObjectClass = newObjectClass;
  this->frame = frame;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->session = session;
  this->isFinished = isLast;
  this->object = new AnnotatorLib::Object(newObjectId, newObjectClass);
  this->annotation = new AnnotatorLib::Annotation(frame, object, AnnotationType::RECTANGLE);
}

AnnotatorLib::Commands::NewAnnotation::NewAnnotation(
    Object *object, AnnotatorLib::Frame *frame, float x, float y, float width, float height,
    AnnotatorLib::Session *session, bool isFinished = false) {
  this->createNewObject = false;
  this->object = object;
  this->frame = frame;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->session = session;
  this->isFinished = isFinished;
  this->annotation = new AnnotatorLib::Annotation(frame, object, AnnotationType::RECTANGLE);
}

bool AnnotatorLib::Commands::NewAnnotation::execute() {
  annotation->setPosition(x, y, width, height);
  session->addAnnotation(annotation); //adds annotation
  session->addObject(object);         //adds object if it does not exist
  session->addFrame(frame);           //adds frame if it does not exist
  return true;
}

bool AnnotatorLib::Commands::NewAnnotation::undo() {
  session->removeAnnotation(annotation); //remove annotation from session, (plus frame and object if empty)

//  if (createNewObject) session->removeObject(object);

//  if (next != nullptr && previous != nullptr) {
//    next->setPrevious(previous);
//    previous->setNext(next);
//  } else {
//    if (next != nullptr) {
//      next->setPrevious(nullptr);
//    }
//    if (previous != nullptr) {
//      previous->setNext(nullptr);
//    }
//  }
  return true;
}

AnnotatorLib::Annotation *
AnnotatorLib::Commands::NewAnnotation::getAnnotation() {
  return annotation;
}
