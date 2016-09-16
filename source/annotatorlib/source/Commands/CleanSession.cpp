#include <AnnotatorLib/Commands/CleanSession.h>

AnnotatorLib::Commands::CleanSession::CleanSession( std::shared_ptr<Session> session) {
  this->session = session;
}

bool AnnotatorLib::Commands::CleanSession::execute() {
  session->clearData();
  return true;
}

bool AnnotatorLib::Commands::CleanSession::undo() {
  //TODO
  return false;
}
