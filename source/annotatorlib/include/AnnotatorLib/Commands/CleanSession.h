// Copyright 2016 Annotator Team
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

  virtual bool execute(Session *informSession = 0) override;

  virtual bool undo(Session *informSession = 0) override;

 protected:
  std::shared_ptr<Session> session;
};
}
}
#endif  // CLEANSESSION_CMD_H
