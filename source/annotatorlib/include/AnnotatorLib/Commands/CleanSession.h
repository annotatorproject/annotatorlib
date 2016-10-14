#ifndef CLEANSESSION_CMD_H
#define CLEANSESSION_CMD_H

#include <AnnotatorLib/Commands/Command.h>
#include <AnnotatorLib/Session.h>
#include <memory>

namespace AnnotatorLib {

namespace Commands {

class ANNOTATORLIB_API CleanSession : public Command {
 public:
  CleanSession() = delete;

  CleanSession(std::shared_ptr<Session> session);

  ~CleanSession() {}

  bool execute();

  bool undo();

 protected:
  std::shared_ptr<Session> session;
};
}
}
#endif  // CLEANSESSION_CMD_H
