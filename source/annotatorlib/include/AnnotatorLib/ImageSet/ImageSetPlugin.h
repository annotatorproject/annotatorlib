// Copyright 2017 Annotator Team
#pragma once

#include <memory>
#include <string>

#include <AnnotatorLib/ImageSet/AbstractImageSet.h>
#include <AnnotatorLib/annotatorlib_api.h>

namespace AnnotatorLib {
namespace ImageSet {

/**
 * @brief The StoragePlugin class
 * Base Class for storage plugins.
 */
class ANNOTATORLIB_API ImageSetPlugin {
 public:
  ImageSetPlugin() {}
  virtual ~ImageSetPlugin() {}

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
  virtual std::shared_ptr<AnnotatorLib::ImageSet::AbstractImageSet> create(
      std::string path) = 0;
};
}
}
