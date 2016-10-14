#ifndef ADJUSTNEIGHBORS_CMD_H
#define ADJUSTNEIGHBORS_CMD_H

#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Session.h>
#include <AnnotatorLib/Commands/Command.h>

#include <memory>
#include <list>

namespace AnnotatorLib {

namespace Commands {

class ANNOTATORLIB_API AdjustNeighbors : public Command {
 public:
  AdjustNeighbors() = delete;

  AdjustNeighbors(std::shared_ptr<Session> session, std::shared_ptr<Annotation> annotation, unsigned int range);

  ~AdjustNeighbors() { }

  bool execute();

  bool undo();

 protected:
  std::shared_ptr<Annotation> annotation;
  std::shared_ptr<Session> session;
  std::list<std::shared_ptr<AnnotatorLib::Commands::Command>> commands;
  unsigned int range;

};
}
}
#endif  // ADJUSTNEIGHBORS_CMD_H
