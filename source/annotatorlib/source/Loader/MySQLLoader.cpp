// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Loader_MySQLLoader_BODY

/************************************************************
 MySQLLoader class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Loader/MySQLLoader.h"

// Derived includes directives

namespace AnnotatorLib {
namespace Loader {

void MySQLLoader::setPath(std::string path) {
  // TODO:
}

StorageType MySQLLoader::getType() { return AnnotatorLib::StorageType::MYSQL; }

void MySQLLoader::loadSession(Session *session) {
  // TODO:
}

// static attributes (if any)

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of MySQLLoader class body
 ************************************************************/
