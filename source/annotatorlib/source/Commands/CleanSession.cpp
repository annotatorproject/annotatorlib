#include <AnnotatorLib/Commands/CleanSession.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::CleanSession::CleanSession(
    AnnotatorLib::Session* session) {
  this->session = session;
}

bool AnnotatorLib::Commands::CleanSession::execute() {
  session->clearAll();
  return true;
}

bool AnnotatorLib::Commands::CleanSession::undo() {
  //TODO
  return false;
}
