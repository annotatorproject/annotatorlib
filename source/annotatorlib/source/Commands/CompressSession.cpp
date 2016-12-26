// Copyright 2016 Annotator Team
#include <AnnotatorLib/Algo/CompressObjectTrack.h>
#include <AnnotatorLib/Commands/CompressSession.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::CompressSession::CompressSession(
    std::shared_ptr<Session> session) {
  this->session = session;
}

bool AnnotatorLib::Commands::CompressSession::execute(
    AnnotatorLib::Session *informSession) {
  // TODO: fix bug
  removed_annotations =
      AnnotatorLib::Algo::CompressObjectTrack::compressSession(this->session);
  if (informSession) {
  }
  return true;
}

bool AnnotatorLib::Commands::CompressSession::undo(
    AnnotatorLib::Session *informSession) {
  for (auto it = removed_annotations.begin(); it != removed_annotations.end();
       it++) {
    session->addAnnotation(*it);
  }
  if (informSession) {
  }
  return true;
}
