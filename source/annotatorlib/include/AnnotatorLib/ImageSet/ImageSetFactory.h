// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_IMAGESETFACTORY_H
#define ANNOTATOR_ANNOTATORLIB_IMAGESETFACTORY_H

/************************************************************
 ImageSetFactory class header
 ************************************************************/

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <AnnotatorLib/ImageSet/ImageSet.h>

namespace AnnotatorLib {

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
  static ImageSet *createImageSet(ImageSetType type, std::string path);

  /**
   *
   * @param type
   * @return imageSet
   */
  static ImageSet *createImageSet(std::string type, std::string path);
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of ImageSetFactory class header
 ************************************************************/

#endif
