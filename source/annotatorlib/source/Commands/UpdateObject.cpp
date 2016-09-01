#include <AnnotatorLib/Commands/UpdateObject.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Class.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::UpdateObject::UpdateObject(
    AnnotatorLib::Object *obj, AnnotatorLib::Class* c) {

  this->obj = obj;
  this->old_class = obj->getClass();
  this->new_class = c;
}

bool AnnotatorLib::Commands::UpdateObject::execute() {
  obj->setClass(new_class);
  return true;
}

bool AnnotatorLib::Commands::UpdateObject::undo() {
  obj->setClass(old_class);
  return true;
}

