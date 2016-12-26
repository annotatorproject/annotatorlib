// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_COMMANDS_COMMAND_H
#define ANNOTATOR_ANNOTATORLIB_COMMANDS_COMMAND_H

/************************************************************
 Annotation command header
 ************************************************************/
#include <AnnotatorLib/annotatorlib_api.h>
#include <vector>

namespace AnnotatorLib {

class Session;

namespace Commands {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API Command {
 public:
  virtual ~Command() {}

  /**
 * @brief execute
 * Let the command make its execution.
 * @param session
 * The session that can be informed about changes.
 * @return
 */
  virtual bool execute(Session *informSession = 0) = 0;

  /**
 * @brief undo
 * Let the command undo its execution.
 * @param session
 * The session that can be informed about changes.
 * @return
 */
  virtual bool undo(Session *informSession = 0) = 0;
};
}  // of namespace Commands
}  // of namespace AnnotatorLib
#endif
