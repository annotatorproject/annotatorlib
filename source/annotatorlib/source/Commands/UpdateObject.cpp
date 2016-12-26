// Copyright 2016 Annotator Team
#include <AnnotatorLib/Class.h>
#include <AnnotatorLib/Commands/UpdateObject.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::UpdateObject::UpdateObject(shared_ptr<Object> obj,
                                                   shared_ptr<Class> c) {
  this->obj = obj;
  this->old_class = obj->getClass();
  this->new_class = c;
}

bool AnnotatorLib::Commands::UpdateObject::execute(
    AnnotatorLib::Session *informSession) {
  obj->setClass(new_class);
  if (informSession) {
    informSession->updateObject(obj);
  }
  return true;
}

bool AnnotatorLib::Commands::UpdateObject::undo(
    AnnotatorLib::Session *informSession) {
  obj->setClass(old_class);
  if (informSession) {
    informSession->updateObject(obj);
  }
  return true;
}
