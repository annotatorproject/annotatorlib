// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_SAVER_MYSQLSAVER_H
#define ANNOTATOR_ANNOTATORLIB_SAVER_MYSQLSAVER_H

/************************************************************
 SQLSaver class header
 ************************************************************/
#include <AnnotatorLib/annotatorlib_api.h>

#include "AnnotatorLib/Storage/AbstractSaver.h"

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API MySQLSaver
    : public AnnotatorLib::Storage::AbstractSaver {
  // AbstractSaver interface
 public:
  void saveAnnotation(const AnnotatorLib::Annotation /* annotation */) override;
  void setPath(std::string /* path */) override;
  AnnotatorLib::StorageType getType() override;
  void saveSession(const AnnotatorLib::Session* /* session */) override;
  void saveProject(std::shared_ptr<AnnotatorLib::Project> project) override;
  bool close() override;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

/************************************************************
 End of MySQLSaver class header
 ************************************************************/

#endif
