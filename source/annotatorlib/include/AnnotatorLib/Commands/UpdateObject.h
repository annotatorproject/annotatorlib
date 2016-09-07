#ifndef UPDATEOBJECT_H
#define UPDATEOBJECT_H

#include <memory>
#include <AnnotatorLib/Commands/Command.h>

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
