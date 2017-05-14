// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_SQLITELOADER_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_SQLITELOADER_H

/************************************************************
 SQLiteLoader class header
 ************************************************************/
#include <AnnotatorLib/Storage/AbstractLoader.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include "../mysql/MySQLLoader.h"

#include <Poco/Data/Session.h>

/************************************************************/
/**
 * @brief The SQLiteLoader class
 * Loads saved data from sqlite database
 */
class ANNOTATORLIB_API SQLiteLoader : public MySQLLoader {
 public:
  AnnotatorLib::StorageType getType() override;
  void loadSession(AnnotatorLib::Session *session) override;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

/************************************************************
 End of SQLiteLoader class header
 ************************************************************/

#endif
