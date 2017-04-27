// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Saver_SQLSaver_BODY

/************************************************************
 SQLSaver class body
 ************************************************************/

// include associated header file

#include "AnnotatorLib/Saver/MySQLSaver.h"

// Derived includes directives

namespace AnnotatorLib {
namespace Saver {

void MySQLSaver::saveAnnotation(const Annotation /* annotation */) {}

void MySQLSaver::setPath(std::string /* path */) {}

StorageType MySQLSaver::getType() { return AnnotatorLib::StorageType::MYSQL; }

void MySQLSaver::saveSession(const Session *) {}

void MySQLSaver::saveProject(std::shared_ptr<Project> project) {
  saveSession(project->getSession().get());
}

bool MySQLSaver::close() { return true; }

// static attributes (if any)

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of SQLSaver class body
 ************************************************************/
