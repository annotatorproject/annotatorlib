#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/NewAnnotation.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::NewAnnotation::NewAnnotation(
    std::string newObjectName, AnnotatorLib::Frame *frame, float x, float y,
    float width, float height, AnnotatorLib::Session *session,
    bool isLast = false) {
  this->createNewObject = true;
  this->newObjectName = newObjectName;
  this->frame = frame;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->session = session;
  this->isFinished = isLast;
  this->object = new AnnotatorLib::Object();
  annotation = new AnnotatorLib::Annotation();
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
  annotation = new AnnotatorLib::Annotation();
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
  annotation = new AnnotatorLib::Annotation();
}

bool AnnotatorLib::Commands::NewAnnotation::execute() {
  annotation->setPosition(x, y, height, height);
  annotation->setObject(object);
  annotation->setFrame(frame);
  object->addAnnotation(annotation);
  frame->addAnnotation(annotation);
  object->addFrame(frame);
  session->addAnnotation(annotation);
  if (createNewObject) {
    object->setName(newObjectName);
    session->addObject(object);
  }

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
  object->removeAnnotation(annotation);
  session->removeAnnotation(annotation);
  frame->removeAnnotation(annotation);

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
