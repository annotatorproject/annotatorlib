#include <AnnotatorLib/Algo/CompressObjectTrack.h>
#include <AnnotatorLib/Commands/CompressSession.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::CompressSession::CompressSession(
    std::shared_ptr<Session> session) {
  this->session = session;
}

bool AnnotatorLib::Commands::CompressSession::execute() {
  // TODO: fix bug
  removed_annotations =
      AnnotatorLib::Algo::CompressObjectTrack::compressSession(this->session);
  return true;
}

bool AnnotatorLib::Commands::CompressSession::undo() {
  for (auto it = removed_annotations.begin(); it != removed_annotations.end();
       it++) {
    session->addAnnotation(*it);
  }
  return true;
}
