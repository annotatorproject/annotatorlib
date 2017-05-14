// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Saver_SQLiteSaver_BODY

#ifdef WITH_SQLITE3
/************************************************************
 SQLSaver class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Saver/SQLiteSaver.h"
#include "AnnotatorLib/Session.h"

// Derived includes directives

namespace AnnotatorLib {
namespace Saver {

void SQLiteSaver::saveAnnotation(Annotation annotation) {}

void SQLiteSaver::setPath(std::string path) { this->path = path; }

StorageType SQLiteSaver::getType() { return AnnotatorLib::sqlite; }

void SQLiteSaver::saveSession(Session *session) {
  int rc = rc = sqlite3_open(path.c_str(), &db);
  if (rc) {
    sqlite3_close(db);
    return;
  }

  createObjectsTable(db);

  for (Object *object : session->getObjects()) {
  }

  createAttributesTable(db);
  for (Attribute *attribute : session->getAttributes()) {
  }

  createAnnotationsTable(db);
  for (Annotation *annotation : session->getAnnotations()) {
  }
}

bool SQLiteSaver::close() {
  sqlite3_close(db);
  return true;
}

int SQLiteSaver::createObjectsTable(sqlite3 *db) {
  char *zErrMsg = 0;
  std::string statement =
      "CREATE TABLE IF NOT EXISTS objects (id INTEGER, name TEXT);";
  int rc = sqlite3_exec(db, statement.c_str(), 0, 0, &zErrMsg);
  sqlite3_free(zErrMsg);
  return rc;
}

int SQLiteSaver::createAttributesTable(sqlite3 *db) {
  char *zErrMsg = 0;
  std::string statement =
      "CREATE TABLE IF NOT EXISTS attributes (id INTEGER, name TEXT, type "
      "TEXT);";
  int rc = sqlite3_exec(db, statement.c_str(), 0, 0, &zErrMsg);
  sqlite3_free(zErrMsg);
  return rc;
}

int SQLiteSaver::createAnnotationsTable(sqlite3 *db) {
  char *zErrMsg = 0;
  std::string statement =
      "CREATE TABLE IF NOT EXISTS annotations (id INTEGER, object INTEGER,"
      "frame INTEGER, next INTEGER, previous INTEGER, type TEXT);";
  int rc = sqlite3_exec(db, statement.c_str(), 0, 0, &zErrMsg);
  sqlite3_free(zErrMsg);
  return rc;
}

// static attributes (if any)

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of SQLSaver class body
 ************************************************************/
#endif  // WITH_SQLITE3
