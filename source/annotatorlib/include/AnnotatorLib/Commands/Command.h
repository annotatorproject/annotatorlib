#ifndef ANNOTATOR_ANNOTATORLIB_COMMANDS_COMMAND_H
#define ANNOTATOR_ANNOTATORLIB_COMMANDS_COMMAND_H

/************************************************************
 Annotation class header
 ************************************************************/
#include <AnnotatorLib/annotatorlib_api.h>
#include <vector>

namespace AnnotatorLib {

namespace Commands {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API Command {
 public:
  virtual ~Command() {}

  virtual bool execute() = 0;

  virtual bool undo() = 0;
};
}
}
#endif
