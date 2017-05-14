// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_SAVER_SQLITESAVER_H
#define ANNOTATOR_ANNOTATORLIB_SAVER_SQLITESAVER_H

/************************************************************
 SQLiteSaver class header
 ************************************************************/
#include <sqlite3.h>

#include <AnnotatorLib/Storage/AbstractSaver.h>
#include <AnnotatorLib/annotatorlib_api.h>

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API SQLiteSaver
    : public AnnotatorLib::Storage::AbstractSaver {
  // AbstractSaver interface
 public:
  void saveAnnotation(const AnnotatorLib::Annotation annotation) override;
  void setPath(std::string path) override;
  AnnotatorLib::StorageType getType() override;
  void saveSession(const AnnotatorLib::Session *session) override;
  void saveProject(std::shared_ptr<AnnotatorLib::Project> project) override;
  bool close() override;

  static int createObjectsTable(sqlite3 *db);
  static int createAttributesTable(sqlite3 *db);
  static int createAnnotationsTable(sqlite3 *db);

 protected:
  std::string path;
  sqlite3 *db;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

/************************************************************
 End of SQLiteSaver class header
 ************************************************************/

#endif
