// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Saver_SQLSaver_BODY

/************************************************************
 SQLSaver class body
 ************************************************************/

// include associated header file

#include "AnnotatorLib/Saver/SQLSaver.h"

// Derived includes directives

namespace AnnotatorLib {
namespace Saver {

void SQLSaver::saveAnnotation(const Annotation annotation) {}

void SQLSaver::setPath(std::string path) {}

StorageType SQLSaver::getType() { return AnnotatorLib::StorageType::SQL; }

void SQLSaver::saveSession(const Session *session) {}

bool SQLSaver::close() { return true; }

// static attributes (if any)

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of SQLSaver class body
 ************************************************************/
