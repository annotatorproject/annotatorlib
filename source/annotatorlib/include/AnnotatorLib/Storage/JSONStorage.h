// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_STORAGE_JSONLOADER_H
#define ANNOTATOR_ANNOTATORLIB_STORAGE_JSONLOADER_H

/************************************************************
 JSONStorage class header
 ************************************************************/
#include <AnnotatorLib/annotatorlib_api.h>
#include <QJsonObject>
#include "AnnotatorLib/Storage/Pkg_Storage.h"

#include "AnnotatorLib/Storage/AbstractStorage.h"

namespace AnnotatorLib {
namespace Storage {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API JSONStorage : public AbstractStorage {
  // AbstractStorage interface
 public:
  bool open();

  bool isOpen();

  bool flush();

  bool isSaved();

  bool close();

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
 End of JSONStorage class header
 ************************************************************/

#endif
