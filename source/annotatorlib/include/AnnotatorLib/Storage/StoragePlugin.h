// Copyright 2017 Annotator Team
#pragma once

#include <string>

#include <AnnotatorLib/Loader/AbstractLoader.h>
#include <AnnotatorLib/Loader/Pkg_Loader.h>
#include <AnnotatorLib/Saver/AbstractSaver.h>
#include <AnnotatorLib/Storage/AbstractStorage.h>
#include <AnnotatorLib/annotatorlib_api.h>

namespace AnnotatorLib {
namespace Storage {

/**
 * @brief The StoragePlugin class
 * Base Class for storage plugins.
 */
class ANNOTATORLIB_API StoragePlugin {
 public:
  StoragePlugin() {}
  virtual ~StoragePlugin() {}

  /**
   * @brief name
   * @return name of the storage plugin
   */
  virtual const std::string name() = 0;

  /**
   * @brief description
   * @return description for the storage plugin
   */
  virtual const std::string description() = 0;

  /**
   * @brief hasLoader
   * @return true if plugin contains loader class
   */
  virtual bool hasLoader() = 0;

  /**
   * @brief hasSaver
   * @return true if plugin contains saver class
   */
  virtual bool hasSaver() = 0;

  /**
   * @brief hasStorage
   * @return true if plugin contains storage class
   */
  virtual bool hasStorage() = 0;

  /**
   * @brief createLoader
   * @return new instance of loader
   */
  virtual shared_ptr<AnnotatorLib::Loader::AbstractLoader> createLoader() = 0;

  /**
   * @brief createSaver
   * @return new instance of saver
   */
  virtual shared_ptr<AnnotatorLib::Saver::AbstractSaver> createSaver() = 0;

  /**
   * @brief createStorage
   * @return new instance of storage
   */
  virtual shared_ptr<AnnotatorLib::Storage::AbstractStorage>
  createStorage() = 0;
};
}
}
