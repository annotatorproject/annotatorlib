// Copyright 2016 Annotator Team
#ifndef ADJUSTNEIGHBORS_CMD_H
#define ADJUSTNEIGHBORS_CMD_H

#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/Command.h>
#include <AnnotatorLib/Session.h>

#include <list>
#include <memory>

namespace AnnotatorLib {

namespace Commands {

class ANNOTATORLIB_API AdjustNeighbors : public Command {
 public:
  AdjustNeighbors() = delete;

  AdjustNeighbors(std::shared_ptr<Session> session,
                  std::shared_ptr<Object> object, std::shared_ptr<Frame> frame,
                  unsigned int range);

  ~AdjustNeighbors() {}

  virtual bool execute(Session *informSession = 0) override;

  virtual bool undo(Session *informSession = 0) override;

 protected:
  std::shared_ptr<Object> object;
  std::shared_ptr<Frame> _frame;
  std::shared_ptr<Session> session;
  std::list<std::shared_ptr<AnnotatorLib::Commands::Command>> commands;
  unsigned int range;
};
}
}
#endif  // ADJUSTNEIGHBORS_CMD_H
