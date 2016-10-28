// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_STORAGEFACTORY_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_STORAGEFACTORY_H

/************************************************************
 StorageFactory class header
 ************************************************************/
#include <string>

#include <AnnotatorLib/Loader/Pkg_Loader.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Storage/AbstractStorage.h>

namespace AnnotatorLib {
namespace Storage {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API StorageFactory {
 public:
  /**
   *
   * @return loader
   * @param type
   */
  static shared_ptr<AbstractStorage> createStorage(std::string /*in*/ type);

  /**
   *
   * @param type
   * @return loader
   */
  static shared_ptr<AbstractStorage> createStorage(
      AnnotatorLib::StorageType type);
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of StorageFactory class header
 ************************************************************/

#endif
