#include <AnnotatorLib/Commands/RemoveObject.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::RemoveObject::RemoveObject(
    AnnotatorLib::Session *session,
    AnnotatorLib::Object *obj) : object(obj), session(session) { }

bool AnnotatorLib::Commands::RemoveObject::execute() {
  bool success = session->removeObject(object);
  return success;
}

bool AnnotatorLib::Commands::RemoveObject::undo() {
  this->session->addObject(this->object);
  return true;
}

