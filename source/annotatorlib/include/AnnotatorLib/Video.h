// Copyright 2016 Annotator Team

#ifndef ANNOTATOR_ANNOTATORLIB_VIDEO_H
#define ANNOTATOR_ANNOTATORLIB_VIDEO_H

/************************************************************
 Video class header
 ************************************************************/

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <AnnotatorLib/ImageSet.h>

namespace cv {
class VideoCapture;
}

namespace AnnotatorLib {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API Video : public ImageSet {
 protected:
  std::string path;

 public:
  Video(std::string path);

  ~Video();

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

  bool gotoPosition(unsigned long position) override;

  long getPosition() override;

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

  virtual std::string getPath();

  virtual bool equals(ImageSet *other);

 protected:
  void initCapture();

  cv::VideoCapture *capture = nullptr;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of Video class header
 ************************************************************/

#endif
