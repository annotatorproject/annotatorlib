// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_SAVER_MYSQLSAVER_H
#define ANNOTATOR_ANNOTATORLIB_SAVER_MYSQLSAVER_H

/************************************************************
 SQLSaver class header
 ************************************************************/
#include <AnnotatorLib/annotatorlib_api.h>
#include "AnnotatorLib/Saver/Pkg_Saver.h"

#include "AnnotatorLib/Saver/AbstractSaver.h"

namespace AnnotatorLib {
namespace Saver {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API MySQLSaver : public AbstractSaver {
  // AbstractSaver interface
 public:
  void saveAnnotation(const Annotation annotation);
  void setPath(std::string path);
  StorageType getType();
  void saveSession(const AnnotatorLib::Session* session);
  bool close();
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of MySQLSaver class header
 ************************************************************/

#endif
