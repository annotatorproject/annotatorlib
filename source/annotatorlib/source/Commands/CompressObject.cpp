// Copyright 2016 Annotator Team
#include <AnnotatorLib/Algo/CompressObjectTrack.h>
#include <AnnotatorLib/Commands/CompressObject.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::CompressObject::CompressObject(
    std::shared_ptr<Session> session, shared_ptr<Object> obj) {
  this->obj = obj;
  this->session = session;
}

bool AnnotatorLib::Commands::CompressObject::execute(
    AnnotatorLib::Session *informSession) {
  removed_annotations = AnnotatorLib::Algo::CompressObjectTrack::compress(
      this->session, this->obj);
  if (informSession) {
    informSession->updateObject(obj);
  }
  return true;
}

bool AnnotatorLib::Commands::CompressObject::undo(
    AnnotatorLib::Session *informSession) {
  for (auto it = removed_annotations.begin(); it != removed_annotations.end();
       it++) {
    session->addAnnotation(*it);
  }
  if (informSession) {
    informSession->updateObject(obj);
  }
  return true;
}
