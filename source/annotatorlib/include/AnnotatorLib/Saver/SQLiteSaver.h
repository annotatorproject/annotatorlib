// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_SAVER_SQLITESAVER_H
#define ANNOTATOR_ANNOTATORLIB_SAVER_SQLITESAVER_H

#ifdef WITH_SQLITE3
/************************************************************
 SQLiteSaver class header
 ************************************************************/
#include <sqlite3.h>

#include <AnnotatorLib/annotatorlib_api.h>
#include "AnnotatorLib/Saver/Pkg_Saver.h"

#include "AnnotatorLib/Saver/AbstractSaver.h"

namespace AnnotatorLib {
namespace Saver {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API SQLiteSaver : public AbstractSaver {
  // AbstractSaver interface
 public:
  void saveAnnotation(const Annotation annotation) override;
  void setPath(std::string path) override;
  StorageType getType() override;
  void saveSession(const AnnotatorLib::Session *session) override;
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

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of SQLiteSaver class header
 ************************************************************/

#endif  // WITH_SQLITE3
#endif
