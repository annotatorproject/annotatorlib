// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Storage_StorageFactory_BODY

/************************************************************
 LoaderFactory class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Storage/StorageFactory.h"
#include "AnnotatorLib/Storage/JSONStorage.h"
#include "AnnotatorLib/Storage/XMLStorage.h"

// Derived includes directives

namespace AnnotatorLib {
namespace Storage {

// static attributes (if any)

AbstractStorage *StorageFactory::createStorage(std::string type) {
  if ("xml" == type) return createStorage(AnnotatorLib::StorageType::XML);
  if ("json" == type) return createStorage(AnnotatorLib::StorageType::JSON);
  if ("sql" == type) return createStorage(AnnotatorLib::StorageType::SQL);
  if ("sqlite" == type) return createStorage(AnnotatorLib::StorageType::SQLITE);
  return createStorage(AnnotatorLib::StorageType::UNKNOWN);
}

AbstractStorage *StorageFactory::createStorage(AnnotatorLib::StorageType type) {
  switch (type) {
    case StorageType::XML:
      return new XMLStorage();
    case StorageType::JSON:
      return new JSONStorage();
    case StorageType::SQL:
    case StorageType::SQLITE:
    default:
      return nullptr;
  }
}

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of LoaderFactory class body
 ************************************************************/
