// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Saver_SaverFactory_BODY

/************************************************************
 SaverFactory class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Saver/SaverFactory.h"
#include "AnnotatorLib/Saver/JSONSaver.h"
#include "AnnotatorLib/Saver/SQLSaver.h"
#include "AnnotatorLib/Saver/SQLiteSaver.h"
#include "AnnotatorLib/Saver/XMLSaver.h"

// Derived includes directives

namespace AnnotatorLib {
namespace Saver {

// static attributes (if any)

AbstractSaver *SaverFactory::createSaver(std::string type) {
  if ("xml" == type) return createSaver(AnnotatorLib::StorageType::XML);
  if ("json" == type) return createSaver(AnnotatorLib::StorageType::JSON);
  if ("sql" == type) return createSaver(AnnotatorLib::StorageType::SQL);
  if ("sqlite" == type) return createSaver(AnnotatorLib::StorageType::SQLITE);
  return createSaver(AnnotatorLib::StorageType::UNKNOWN);
}

AbstractSaver *SaverFactory::createSaver(
    AnnotatorLib::StorageType /*in*/ type) {
  switch (type) {
    case StorageType::XML:
      return new XMLSaver();
    case StorageType::JSON:
      return new JSONSaver();
    case StorageType::SQL:
      return new SQLSaver();
#ifdef WITH_SQLITE3
    case StorageType::SQLITE:
      return new SQLiteSaver();
#endif
    default:
      return nullptr;
  }
}

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of SaverFactory class body
 ************************************************************/
