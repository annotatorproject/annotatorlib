// Copyright 2016 Annotator Team
#ifndef UPDATEOBJECT_H
#define UPDATEOBJECT_H

#include <AnnotatorLib/Commands/Command.h>
#include <memory>

using std::shared_ptr;

namespace AnnotatorLib {

class Session;
class Object;
class Class;

namespace Commands {

class ANNOTATORLIB_API UpdateObject : public Command {
 public:
  UpdateObject() = delete;

  UpdateObject(shared_ptr<Object> obj, shared_ptr<Class> c);

  ~UpdateObject() {}

  shared_ptr<Object> getObject() { return obj; }

  bool execute();

  bool undo();

 protected:
  shared_ptr<Object> obj;
  shared_ptr<Class> new_class;
  shared_ptr<Class> old_class;
};
}
}
#endif  // UPDATEANNOTATION_H
