#ifndef COMPRESSSESSION_CMD_H
#define COMPRESSSESSION_CMD_H

#include <AnnotatorLib/Commands/Command.h>
#include <vector>

namespace AnnotatorLib {

class Session;
class Annotation;

namespace Commands {

class ANNOTATORLIB_API CompressSession : public Command {
 public:
  CompressSession() = delete;

  CompressSession(Session* session);

  ~CompressSession() {}

  bool execute();

  bool undo();

 protected:
  Session* session = nullptr;

 private:
  std::vector<Annotation*> removed_annotations;
};
}
}
#endif  // UPDATEANNOTATION_H
