#ifndef REMOVEOBJECT
#define REMOVEOBJECT

#include <AnnotatorLib/Commands/Command.h>
#include <memory>

using std::shared_ptr;

namespace AnnotatorLib {

class Session;
class Object;

namespace Commands {

class ANNOTATORLIB_API RemoveObject : public Command {
 public:
  RemoveObject() = delete;
  RemoveObject(Session * s, shared_ptr<Object> o);
  ~RemoveObject() {}

  bool execute();

  bool undo();

 protected:
  Session *session;
  const shared_ptr<Object> object;
};
}
}
#endif  // REMOVEOBJECT
