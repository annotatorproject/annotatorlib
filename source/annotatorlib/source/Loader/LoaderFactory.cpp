// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Loader_LoaderFactory_BODY

/************************************************************
 LoaderFactory class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Loader/LoaderFactory.h"
#include "AnnotatorLib/Loader/JSONLoader.h"
#include "AnnotatorLib/Loader/MySQLLoader.h"
#include "AnnotatorLib/Loader/XMLLoader.h"

// Derived includes directives

namespace AnnotatorLib {
namespace Loader {

// static attributes (if any)

AbstractLoader *LoaderFactory::createLoader(std::string type) {
  if ("xml" == type) return createLoader(AnnotatorLib::StorageType::XML);
  if ("json" == type) return createLoader(AnnotatorLib::StorageType::JSON);
  if ("mysql" == type) return createLoader(AnnotatorLib::StorageType::MYSQL);
  if ("sqlite" == type) return createLoader(AnnotatorLib::StorageType::SQLITE);
  return createLoader(AnnotatorLib::StorageType::UNKNOWN);
}

AbstractLoader *LoaderFactory::createLoader(AnnotatorLib::StorageType type) {
  switch (type) {
    case StorageType::XML:
      return new XMLLoader();
    case StorageType::JSON:
      return new JSONLoader();
    case StorageType::MYSQL:
      return new MySQLLoader();
    case StorageType::SQLITE:
      return nullptr;
    default:
      return nullptr;
  }
}

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of LoaderFactory class body
 ************************************************************/
