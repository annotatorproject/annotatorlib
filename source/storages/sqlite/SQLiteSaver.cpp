// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Saver_SQLiteSaver_BODY

/************************************************************
 SQLSaver class body
 ************************************************************/

// include associated header file
#include "SQLiteSaver.h"
#include "AnnotatorLib/Session.h"

// Derived includes directives

void SQLiteSaver::saveAnnotation(AnnotatorLib::Annotation annotation) {}

void SQLiteSaver::setPath(std::string path) { this->path = path; }

AnnotatorLib::StorageType SQLiteSaver::getType() {
  return AnnotatorLib::StorageType::SQLITE;
}

void SQLiteSaver::saveSession(const AnnotatorLib::Session *session) {}

void SQLiteSaver::saveProject(std::shared_ptr<AnnotatorLib::Project> project) {
  saveSession(project->getSession().get());
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

/************************************************************
 End of SQLSaver class body
 ************************************************************/
