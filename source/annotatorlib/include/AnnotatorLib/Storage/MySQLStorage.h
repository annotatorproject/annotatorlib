// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_STORAGE_MYSQLSTORAGE_H
#define ANNOTATOR_ANNOTATORLIB_STORAGE_MYSQLSTORAGE_H

/************************************************************
 MySQLStorage class header
 ************************************************************/
#include <AnnotatorLib/annotatorlib_api.h>
#include <QJsonObject>
#include "AnnotatorLib/Storage/Pkg_Storage.h"

#include "AnnotatorLib/Storage/AbstractStorage.h"

namespace AnnotatorLib {
namespace Storage {

/************************************************************/
/**
 * @brief The MySQLStorage class
 */
class ANNOTATORLIB_API MySQLStorage : public AbstractStorage {
  // AbstractStorage interface
 public:
  bool open();

  bool isOpen();

  bool flush();

  bool isSaved();

  bool close();

  /**
   * @brief setPath
   * @param path
   * Path should be like: "host=localhost;user=annotator;password=annotator;db=annotator;auto-reconnect=true";
   */
  void setPath(std::string path);

  StorageType getType();

 protected:
  std::string path;

  bool _open = false;
  bool _save = true;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of MySQLStorage class header
 ************************************************************/

#endif
