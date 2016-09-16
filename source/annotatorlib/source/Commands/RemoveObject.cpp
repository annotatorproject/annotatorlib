#include <AnnotatorLib/Commands/RemoveObject.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::RemoveObject::RemoveObject(
    std::shared_ptr<Session> session, shared_ptr<Object> obj)
    : session(session), object(obj) { }

bool AnnotatorLib::Commands::RemoveObject::execute() {
  shared_ptr<Object> removed_obj = session->removeObject(object->getId(), true);
  return removed_obj.get() == object.get();
}

bool AnnotatorLib::Commands::RemoveObject::undo() {
  return this->session->addObject(this->object);
}
