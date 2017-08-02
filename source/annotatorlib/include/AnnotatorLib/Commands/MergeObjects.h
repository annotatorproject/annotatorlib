// Copyright 2017 Annotator Team
#ifndef MERGEOBJECTS_H
#define MERGEOBJECTS_H

#include <AnnotatorLib/Commands/Command.h>
#include <memory>

namespace AnnotatorLib {

class Session;
class Object;
class Class;

namespace Commands {

class ANNOTATORLIB_API MergeObjects : public Command {
 public:
  MergeObjects() = delete;

  MergeObjects(std::shared_ptr<Session> session, std::shared_ptr<Object> first,
               std::shared_ptr<Object> second);

  ~MergeObjects() {}

  virtual bool execute(Session *informSession = 0) override;

  virtual bool undo(Session *informSession = 0) override;

 protected:
  std::shared_ptr<Session> session;
  std::shared_ptr<Object> first;
  std::shared_ptr<Object> second;
};
}
}
#endif  // MERGEOBJECTS_H
