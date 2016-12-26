// Copyright 2016 Annotator Team
#include <AnnotatorLib/Commands/CleanSession.h>

AnnotatorLib::Commands::CleanSession::CleanSession(
    std::shared_ptr<Session> session) {
  this->session = session;
}

bool AnnotatorLib::Commands::CleanSession::execute(
    AnnotatorLib::Session *informSession) {
  session->clearData();
  return true;
}

bool AnnotatorLib::Commands::CleanSession::undo(
    AnnotatorLib::Session *informSession) {
  // TODO
  return false;
}
