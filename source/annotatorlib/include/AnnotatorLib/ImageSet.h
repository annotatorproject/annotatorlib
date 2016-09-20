// Copyright 2016 Annotator Team

#ifndef ANNOTATOR_ANNOTATORLIB_IMAGESET_H
#define ANNOTATOR_ANNOTATORLIB_IMAGESET_H

/************************************************************
 ImageSet class header
 ************************************************************/
#include <string>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Image.h>
#include <AnnotatorLib/annotatorlib_api.h>

namespace AnnotatorLib {

/************************************************************/

class ANNOTATORLIB_API ImageSet {
 public:
  /**
   *
   * @return type
   */
  virtual ImageSetType getType() = 0;

  /**
   *
   * @param frame
   * @return image
   */
  virtual Image getImage(unsigned int /*in*/ frame) = 0;

  virtual bool gotoPosition(unsigned long position) = 0;

  virtual long getPosition() = 0;

  /**
   *
   * @return next
   */
  virtual bool hasNext() = 0;

  /**
   *
   * @return image
   */
  virtual Image next() = 0;

  /**
   *
*@return size of image set. In Videos its the number of Frames,
* in Folders its the number of Image Files.
   */
  virtual unsigned int size() = 0;

  virtual std::string getPath() = 0;

  virtual bool equals(ImageSet *other) = 0;

  virtual ~ImageSet() {}
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of ImageSet class header
 ************************************************************/

#endif
