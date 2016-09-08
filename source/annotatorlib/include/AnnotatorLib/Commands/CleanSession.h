#ifndef CLEANSESSION_CMD_H
#define CLEANSESSION_CMD_H

#include <AnnotatorLib/Commands/Command.h>

namespace AnnotatorLib {

class Session;

namespace Commands {

class ANNOTATORLIB_API CleanSession : public Command {
 public:
  CleanSession() = delete;

  CleanSession(Session* session);

  ~CleanSession() { }

  bool execute();

  bool undo();

 protected:
  Session* session;

};
}
}
#endif  // CLEANSESSION_CMD_H
