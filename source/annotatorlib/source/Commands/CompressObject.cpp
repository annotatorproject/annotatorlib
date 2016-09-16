#include <AnnotatorLib/Algo/CompressObjectTrack.h>
#include <AnnotatorLib/Commands/CompressObject.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::CompressObject::CompressObject(
    std::shared_ptr<Session> session, shared_ptr<Object> obj) {
  this->obj = obj;
  this->session = session;
}

bool AnnotatorLib::Commands::CompressObject::execute() {
  removed_annotations = AnnotatorLib::Algo::CompressObjectTrack::compress(
      this->session, this->obj);
  return true;
}

bool AnnotatorLib::Commands::CompressObject::undo() {
  for (auto it = removed_annotations.begin(); it != removed_annotations.end();
       it++) {
    session->addAnnotation(*it);
  }
  return true;
}
