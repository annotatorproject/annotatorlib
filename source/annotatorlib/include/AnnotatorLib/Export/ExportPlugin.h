// Copyright 2017 Annotator Team
#pragma once

#include <memory>
#include <string>

#include <AnnotatorLib/Export/AbstractExport.h>
#include <AnnotatorLib/annotatorlib_api.h>

namespace AnnotatorLib {
namespace Export {

/**
 * @brief The StoragePlugin class
 * Base Class for storage plugins.
 */
class ANNOTATORLIB_API ExportPlugin {
 public:
  ExportPlugin() {}
  virtual ~ExportPlugin() {}

  /**
   * @brief name
   * @return name of the imageset plugin
   */
  virtual const std::string name() = 0;

  /**
   * @brief description
   * @return description for the imageset plugin
   */
  virtual const std::string description() = 0;

  /**
   * @brief createLoader
   * @return new instance of loader
   */
  virtual std::shared_ptr<AnnotatorLib::Export::AbstractExport> create(
      std::string path) = 0;
};
}
}
