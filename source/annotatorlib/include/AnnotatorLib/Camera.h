// Copyright 2016 Annotator Team

#ifndef ANNOTATOR_ANNOTATORLIB_CAMERA_H
#define ANNOTATOR_ANNOTATORLIB_CAMERA_H

/************************************************************
 ImageFolder class header
 ************************************************************/

#include <vector>

#include <opencv2/opencv.hpp>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include "AnnotatorLib/ImageSet.h"

namespace AnnotatorLib {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API Camera : public ImageSet {
 public:
  Camera(std::string path);

  /**
   *
   * @return type
   */
  virtual ImageSetType getType();

  /**
   *
   * @param frame
   * @return image
   */
  virtual Image getImage(unsigned long /*in*/ frame) override;

  virtual bool gotoPosition(unsigned long position) override;

  virtual long getPosition() override;

  /**
   *
   * @return next
   */
  virtual bool hasNext();

  /**
   *
   * @return image
   */
  virtual Image next();

  /**
   *
   * @return size
   */
  virtual unsigned int size();

  virtual unsigned int getFPS() override;

  virtual std::string getPath();

  virtual bool equals(ImageSet *other);

 protected:
  void initCamera();

  std::string path;

  cv::VideoCapture capture;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of Camera class header
 ************************************************************/

#endif
