// Copyright 2017 Annotator Team
#include <AnnotatorLib/Class.h>
#include <AnnotatorLib/Commands/MergeObjects.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::MergeObjects::MergeObjects(
    std::shared_ptr<Session> session, shared_ptr<Object> first,
    shared_ptr<Object> second)
    : session(session) {
  this->first = first;
  this->second = second;
}

bool AnnotatorLib::Commands::MergeObjects::execute(
    AnnotatorLib::Session *informSession) {
  bool success = false;
  first->setActive(true);
  for (auto &pair : second->getAnnotations()) {
    auto annotation = Annotation::make_shared(pair.second.lock(), first);
    success = session->addAnnotation(annotation, true);
    session->removeAnnotation(pair.second.lock()->getId(), true);
  }

  for (auto &attribute : second->getAttributes()) {
    first->addAttribute(attribute);
    second->removeAttribute(attribute);
  }

  first->setActive(false);

  session->removeObject(second->getId());

  if (informSession) {
    informSession->updateObject(first);
    informSession->updateObject(second);
  }
  return success;
}

bool AnnotatorLib::Commands::MergeObjects::undo(
    AnnotatorLib::Session *informSession) {
  return false;
}
