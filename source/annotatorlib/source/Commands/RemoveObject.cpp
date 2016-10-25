// Copyright 2016 Annotator Team
#include <AnnotatorLib/Commands/RemoveObject.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::RemoveObject::RemoveObject(
    std::shared_ptr<Session> session, shared_ptr<Object> obj)
    : session(session), object(obj) {}

bool AnnotatorLib::Commands::RemoveObject::execute() {
  for (auto& pair : object->getAnnotations()) {
    removedAnnotations.push_back(pair.second.lock());
  }
  shared_ptr<Object> removed_obj = session->removeObject(object->getId());
  return removed_obj == object;
}

bool AnnotatorLib::Commands::RemoveObject::undo() {
  for (auto& annotation : removedAnnotations) {
    session->addAnnotation(annotation, false);
  }
  return this->session->addObject(this->object);
}
