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
    Object *object, Frame *frame, float x, float y, float width, float height,
    Session *session, bool isFinished = false) {
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

AnnotatorLib::Commands::NewAnnotation::NewAnnotation(
    AnnotatorLib::Object *object, AnnotatorLib::Frame *frame, float x, float y,
    float width, float height, AnnotatorLib::Annotation *next,
    AnnotatorLib::Annotation *previous, AnnotatorLib::Session *session,
    bool isFinished = false) {
  this->object = object;
  this->frame = frame;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->next = next;
  this->previous = previous;
  this->session = session;
  this->isFinished = isFinished;
  this->annotation = new AnnotatorLib::Annotation(frame, object, AnnotationType::RECTANGLE);
}

bool AnnotatorLib::Commands::NewAnnotation::execute() {
  annotation->setPosition(x, y, height, height);
  annotation->setVisible(true);
  session->addAnnotation(annotation); //adds annotation plus object and frame if they do not exist

  if (next != nullptr) {
    annotation->setNext(next);
    next->setPrevious(annotation);
  } else {
    if (isFinished) annotation->setFinished(true);
  }

  if (previous != nullptr) {
    annotation->setPrevious(previous);
    previous->setNext(annotation);
  }

  return true;
}

bool AnnotatorLib::Commands::NewAnnotation::undo() {
  session->removeAnnotation(annotation); //remove annotation from session, frame and object
  annotation->setVisible(false);

  if (createNewObject) session->removeObject(object);

  if (next != nullptr && previous != nullptr) {
    next->setPrevious(previous);
    previous->setNext(next);
  } else {
    if (next != nullptr) {
      next->setPrevious(nullptr);
    }
    if (previous != nullptr) {
      previous->setNext(nullptr);
    }
  }
  return true;
}

AnnotatorLib::Annotation *
AnnotatorLib::Commands::NewAnnotation::getAnnotation() {
  return annotation;
}
