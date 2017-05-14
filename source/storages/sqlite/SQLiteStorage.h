// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_STORAGE_SQLITESTORAGE_H
#define ANNOTATOR_ANNOTATORLIB_STORAGE_SQLITESTORAGE_H

/************************************************************
 MySQLStorage class header
 ************************************************************/
#include <AnnotatorLib/Storage/AbstractStorage.h>
#include <AnnotatorLib/Storage/MySQLStorage.h>
#include <AnnotatorLib/Storage/Pkg_Storage.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <Poco/Data/SessionPool.h>

/************************************************************/
/**
 * @brief The SQLiteStorage class
 */
class ANNOTATORLIB_API SQLiteStorage
    : public AnnotatorLib::Storage::MySQLStorage {
 public:
  ~SQLiteStorage();

  bool open() override;

  /**
   * @brief setPath
   * @param path
   * Path should be like:
   * "annotator.db";
   */
  void setPath(std::string path) override;

  AnnotatorLib::StorageType getType() override;

  void createTables() override;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

/************************************************************
 End of SQLiteStorage class header
 ************************************************************/

#endif
