// Copyright 2016 Annotator Team

#ifndef ANNOTATOR_ANNOTATORLIB_CAMERA_H
#define ANNOTATOR_ANNOTATORLIB_CAMERA_H

/************************************************************
 ImageFolder class header
 ************************************************************/

#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include "AnnotatorLib/ImageSet/AbstractImageSet.h"

namespace AnnotatorLib {
namespace ImageSet {
/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API Camera : public AbstractImageSet {
 public:
  Camera(std::string path);

  /**
   *
   * @return type
   */
  virtual ImageSetType getType() override;

  /**
   *
   * @param frame
   * @return image
   */
  virtual Image getImage(unsigned long /* frame */) override;

  virtual std::string getImagePath(unsigned long /* frame */) override;

  virtual bool gotoPosition(unsigned long /* position */) override;

  virtual long getPosition() override;

  /**
   *
   * @return next
   */
  virtual bool hasNext() override;

  /**
   *
   * @return image
   */
  virtual Image next() override;

  /**
   *
   * @return size
   */
  virtual unsigned int size() override;

  virtual unsigned int getFPS() override;

  virtual std::string getPath() override;

  virtual bool equals(std::shared_ptr<AbstractImageSet> other) override;

 protected:
  void initCamera();

  std::string path;

  cv::VideoCapture capture;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */
}  // of namespace ImageSet
}  // of namespace AnnotatorLib

/************************************************************
 End of Camera class header
 ************************************************************/

#endif
