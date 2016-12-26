// Copyright 2016 Annotator Team
#include <AnnotatorLib/Commands/RemoveObject.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::RemoveObject::RemoveObject(
    std::shared_ptr<Session> session, shared_ptr<Object> obj)
    : session(session), object(obj) {}

bool AnnotatorLib::Commands::RemoveObject::execute(
    AnnotatorLib::Session* informSession) {
  for (auto& pair : object->getAnnotations()) {
    removedAnnotations.push_back(pair.second.lock());
  }
  shared_ptr<Object> removed_obj = session->removeObject(object->getId());
  bool success = removed_obj == object;
  if (informSession) {
    informSession->updateObject(object);
  }
  return success;
}

bool AnnotatorLib::Commands::RemoveObject::undo(
    AnnotatorLib::Session* informSession) {
  for (auto& annotation : removedAnnotations) {
    session->addAnnotation(annotation, false);
  }
  bool success = this->session->addObject(this->object);
  if (informSession) {
    informSession->updateObject(object);
  }
  return success;
}
