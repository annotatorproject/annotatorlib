// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_SAVER_ABSTRACTSAVER_H
#define ANNOTATOR_ANNOTATORLIB_SAVER_ABSTRACTSAVER_H

/************************************************************
 AbstractSaver class header
 ************************************************************/

#include <AnnotatorLib/annotatorlib_api.h>
#include <string>

#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Project.h>

namespace AnnotatorLib {

class Session;

namespace Storage {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API AbstractSaver {
 public:
  /**
   *
   * @param annotation
   */
  virtual void saveAnnotation(
      const AnnotatorLib::Annotation /*in*/ annotation) = 0;

  /**
   *
   * @param path
   */
  virtual void setPath(std::string /*in*/ path) = 0;

  /**
   *
   * @return type
   */
  virtual AnnotatorLib::StorageType getType() = 0;

  virtual void saveSession(const AnnotatorLib::Session* session) = 0;

  virtual void saveProject(std::shared_ptr<AnnotatorLib::Project> project) = 0;

  virtual bool close() = 0;

  virtual ~AbstractSaver() {}
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of AbstractSaver class header
 ************************************************************/

#endif
