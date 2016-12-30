// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_SQLITELOADER_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_SQLITELOADER_H

/************************************************************
 MySQLLoader class header
 ************************************************************/
#include <AnnotatorLib/Loader/AbstractLoader.h>
#include <AnnotatorLib/Loader/Pkg_Loader.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include <AnnotatorLib/Loader/MySQLLoader.h>

#include <Poco/Data/Session.h>

namespace AnnotatorLib {
namespace Loader {

/************************************************************/
/**
 * @brief The SQLiteLoader class
 * Loads saved data from sqlite database
 */
class ANNOTATORLIB_API SQLiteLoader : public MySQLLoader {
 public:
  StorageType getType() override;
  void loadSession(AnnotatorLib::Session *session) override;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of SQLiteLoader class header
 ************************************************************/

#endif
