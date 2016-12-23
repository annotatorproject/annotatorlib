// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_MYSQLLOADER_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_MYSQLLOADER_H

/************************************************************
 SQLLoader class header
 ************************************************************/
#include <AnnotatorLib/annotatorlib_api.h>
#include "AnnotatorLib/Loader/Pkg_Loader.h"

#include "AnnotatorLib/Loader/AbstractLoader.h"

namespace AnnotatorLib {
namespace Loader {

/************************************************************/
/**
 * @brief The MySQLLoader class
 * Loads saved data from mysql database
 */
class ANNOTATORLIB_API MySQLLoader : public AbstractLoader {
  // AbstractLoader interface
 public:
  void setPath(std::string path);
  StorageType getType();
  void loadSession(AnnotatorLib::Session* session);
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of MySQLLoader class header
 ************************************************************/

#endif
