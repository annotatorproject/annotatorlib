#ifndef COMPRESSOBJECT_CMD_H
#define COMPRESSOBJECT_CMD_H

#include <AnnotatorLib/Commands/Command.h>
#include <vector>
#include <memory>

using std::shared_ptr;

namespace AnnotatorLib {

class Session;
class Object;
class Annotation;

namespace Commands {

class ANNOTATORLIB_API CompressObject : public Command {
 public:
  CompressObject() = delete;

  CompressObject(Session* session, shared_ptr<Object> obj);

  ~CompressObject() {
    removed_annotations.clear();
  }

  bool execute();

  bool undo();

 protected:
  shared_ptr<Object> obj;
  Session* session;

 private:
  std::vector<shared_ptr<Annotation>> removed_annotations;
};
}
}
#endif  // UPDATEANNOTATION_H
