// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_IMAGESETFACTORY_H
#define ANNOTATOR_ANNOTATORLIB_IMAGESETFACTORY_H

/************************************************************
 ImageSetFactory class header
 ************************************************************/

#include <list>
#include <map>
#include <memory>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/ImageSet/AbstractImageSet.h>
#include <AnnotatorLib/ImageSet/ImageSetPlugin.h>
#include <AnnotatorLib/annotatorlib_api.h>

namespace AnnotatorLib {
namespace ImageSet {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API ImageSetFactory {
 public:
  /**
   *
   * @param type
   * @return imageSet
   */
  std::shared_ptr<AbstractImageSet> createImageSet(std::string type,
                                                   std::string path);

  std::list<std::string> availableImageSets();

  /**
   * @brief loadPlugins
   * @param dir the path to plugins
   */
  void loadPlugins(std::string dir);

  /**
   * @brief instance
   * @return singleton for StorageFactory
   */
  static ImageSetFactory* instance();

  ~ImageSetFactory();

 protected:
  void addAvailableImageSet(ImageSetPlugin* plugin);

 private:
  ImageSetFactory() {}
  std::list<std::string> _availableImageSets{"images", "imagefolder"};
  std::map<std::string, std::shared_ptr<ImageSetPlugin>> plugins;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace ImageSet
}  // of namespace AnnotatorLib

/************************************************************
 End of ImageSetFactory class header
 ************************************************************/

#endif
