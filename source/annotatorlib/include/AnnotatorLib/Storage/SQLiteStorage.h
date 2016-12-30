// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_STORAGE_SQLITESTORAGE_H
#define ANNOTATOR_ANNOTATORLIB_STORAGE_SQLITESTORAGE_H

/************************************************************
 MySQLStorage class header
 ************************************************************/
#include <AnnotatorLib/Storage/AbstractStorage.h>
#include <AnnotatorLib/Storage/Pkg_Storage.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include <AnnotatorLib/Storage/MySQLStorage.h>
#include <QJsonObject>

#include <Poco/Data/SessionPool.h>

namespace AnnotatorLib {
namespace Storage {

/************************************************************/
/**
 * @brief The SQLiteStorage class
 */
class ANNOTATORLIB_API SQLiteStorage : public MySQLStorage {

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

  StorageType getType() override;

  void createTables() override;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of SQLiteStorage class header
 ************************************************************/

#endif
