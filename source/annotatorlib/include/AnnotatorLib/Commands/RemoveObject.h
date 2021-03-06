// Copyright 2016 Annotator Team
#ifndef REMOVEOBJECT
#define REMOVEOBJECT

#include <AnnotatorLib/Commands/Command.h>
#include <memory>

using std::shared_ptr;

namespace AnnotatorLib {

class Session;
class Object;
class Annotation;

namespace Commands {

class ANNOTATORLIB_API RemoveObject : public Command {
 public:
  RemoveObject() = delete;
  RemoveObject(std::shared_ptr<Session> s, shared_ptr<Object> o);
  RemoveObject(const RemoveObject &other) = delete;
  ~RemoveObject() {}

  virtual bool execute(Session *informSession = 0) override;

  virtual bool undo(Session *informSession = 0) override;

  shared_ptr<Object> getObject() { return object; }

 protected:
  std::vector<std::shared_ptr<Annotation>> removedAnnotations;
  std::shared_ptr<Session> session;
  const shared_ptr<Object> object;
};
}
}
#endif  // REMOVEOBJECT
