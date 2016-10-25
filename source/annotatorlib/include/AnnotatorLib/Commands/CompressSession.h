// Copyright 2016 Annotator Team
#ifndef COMPRESSSESSION_CMD_H
#define COMPRESSSESSION_CMD_H

#include <AnnotatorLib/Commands/Command.h>
#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

namespace AnnotatorLib {

class Session;
class Annotation;

namespace Commands {

class ANNOTATORLIB_API CompressSession : public Command {
 public:
  CompressSession() = delete;

  CompressSession(std::shared_ptr<Session> session);

  ~CompressSession() { removed_annotations.clear(); }

  bool execute();

  bool undo();

 protected:
  std::shared_ptr<Session> session;

 private:
  vector<shared_ptr<Annotation>> removed_annotations;
};
}
}
#endif  // UPDATEANNOTATION_H
