// Copyright 2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_STORAGEFACTORY_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_STORAGEFACTORY_H

/************************************************************
 StorageFactory class header
 ************************************************************/
#include <map>
#include <string>

#include <AnnotatorLib/Loader/Pkg_Loader.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Storage/AbstractStorage.h>
#include <AnnotatorLib/Storage/StoragePlugin.h>

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
  shared_ptr<AbstractStorage> createStorage(std::string /*in*/ type);

  /**
   *
   * @param type
   * @return loader
   */
  shared_ptr<AbstractStorage> createStorage(AnnotatorLib::StorageType type);

  /**
   * @brief loadPlugins
   * @param dir the path to plugins
   */
  void loadPlugins(std::string dir);

  /**
   * @brief instance
   * @return singleton for StorageFactory
   */
  static StorageFactory* instance() {
    if (!_instance) _instance = new StorageFactory();
    return _instance;
  }

  ~StorageFactory() { _instance = 0; }

 private:
  static StorageFactory* _instance;
  StorageFactory() {}

  std::map<std::string, std::shared_ptr<StoragePlugin>> plugins;
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
