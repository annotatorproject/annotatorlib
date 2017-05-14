// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Saver_MySQLSaver_BODY

/************************************************************
 SQLSaver class body
 ************************************************************/

// include associated header file

#include "MySQLSaver.h"

// Derived includes directives

void MySQLSaver::saveAnnotation(
    const AnnotatorLib::Annotation /* annotation */) {}

void MySQLSaver::setPath(std::string /* path */) {}

AnnotatorLib::StorageType MySQLSaver::getType() {
  return AnnotatorLib::StorageType::MYSQL;
}

void MySQLSaver::saveSession(const AnnotatorLib::Session *) {}

void MySQLSaver::saveProject(std::shared_ptr<AnnotatorLib::Project> project) {
  saveSession(project->getSession().get());
}

bool MySQLSaver::close() { return true; }

/************************************************************
 End of SQLSaver class body
 ************************************************************/
