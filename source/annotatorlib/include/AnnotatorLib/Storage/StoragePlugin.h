// Copyright 2017 Annotator Team
#pragma once

#include <string>

#include <AnnotatorLib/Loader/Pkg_Loader.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include <AnnotatorLib/Storage/AbstractStorage.h>
#include <AnnotatorLib/Loader/AbstractLoader.h>
#include <AnnotatorLib/Saver/AbstractSaver.h>

namespace AnnotatorLib {
namespace Storage {

/**
 * @brief The HyphaBasePlugin class
 *      Base Plugin for all handler and plugins.
 *      Will run as its own thread.
 */
class ANNOTATORLIB_API StoragePlugin {
 public:
  StoragePlugin() {}
  virtual ~StoragePlugin() {}

  virtual const std::string name() = 0;
  virtual const std::string description() = 0;

  virtual bool hasLoader() = 0;
  virtual bool hasSaver() = 0;
  virtual bool hasStorage() = 0;

  virtual shared_ptr<AnnotatorLib::Loader::AbstractLoader> createLoader() = 0;
  virtual shared_ptr<AnnotatorLib::Saver::AbstractSaver> createSaver() = 0;
  virtual shared_ptr<AnnotatorLib::Storage::AbstractStorage> createStorage() = 0;
};
}
}
