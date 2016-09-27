#include <AnnotatorLib/Commands/RemoveObject.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::RemoveObject::RemoveObject(
    std::shared_ptr<Session> session, shared_ptr<Object> obj)
    : session(session), object(obj) { }

bool AnnotatorLib::Commands::RemoveObject::execute() {
  shared_ptr<Object> removed_obj = session->removeObject(object->getId(), false);
  for (auto& pair : removed_obj->getAnnotations()) {
      session->removeAnnotation(pair.second.lock()->getId());
      annotations.push_back(pair.second);
  }
  return removed_obj == object;
}

bool AnnotatorLib::Commands::RemoveObject::undo() {

  for (auto& annotation : annotations) {
      session->addAnnotation(annotation.lock(), false);
  }  
  return this->session->addObject(this->object);
}
