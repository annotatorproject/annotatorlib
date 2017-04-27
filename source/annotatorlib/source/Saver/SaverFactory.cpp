// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Saver_SaverFactory_BODY

/************************************************************
 SaverFactory class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Saver/SaverFactory.h"
#include "AnnotatorLib/Saver/JSONSaver.h"
#include "AnnotatorLib/Saver/MySQLSaver.h"
#include "AnnotatorLib/Saver/PascalVocXMLSaver.h"
#include "AnnotatorLib/Saver/SQLiteSaver.h"
#include "AnnotatorLib/Saver/XMLSaver.h"

// Derived includes directives

namespace AnnotatorLib {
namespace Saver {

// static attributes (if any)

AbstractSaver *SaverFactory::createSaver(std::string type) {
  if ("xml" == type) return createSaver(AnnotatorLib::StorageType::XML);
  if ("pascalvocxml" == type)
    return createSaver(AnnotatorLib::StorageType::PASCALVOCXML);
  if ("json" == type) return createSaver(AnnotatorLib::StorageType::JSON);
  if ("mysql" == type) return createSaver(AnnotatorLib::StorageType::MYSQL);
  if ("sqlite" == type) return createSaver(AnnotatorLib::StorageType::SQLITE);
  return createSaver(AnnotatorLib::StorageType::UNKNOWN);
}

AbstractSaver *SaverFactory::createSaver(
    AnnotatorLib::StorageType /*in*/ type) {
  switch (type) {
    case StorageType::XML:
      return new XMLSaver();
    case StorageType::PASCALVOCXML:
      return new PascalVocXMLSaver();
    case StorageType::JSON:
      return new JSONSaver();
    case StorageType::MYSQL:
      return new MySQLSaver();
#ifdef WITH_SQLITE3
    case StorageType::SQLITE:
      return new SQLiteSaver();
#endif
    default:
      return nullptr;
  }
}

std::list<std::string> SaverFactory::availableSaver() {
  std::list<std::string> savers;
  savers.push_back("xml");
  savers.push_back("pascalvocxml");
  savers.push_back("json");
  savers.push_back("mysql");
#ifdef WITH_SQLITE3
  savers.push_back("sqlite");
#endif
  return savers;
}

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of SaverFactory class body
 ************************************************************/
