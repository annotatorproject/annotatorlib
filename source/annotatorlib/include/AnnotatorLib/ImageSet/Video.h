// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_VIDEO_H
#define ANNOTATOR_ANNOTATORLIB_VIDEO_H

/************************************************************
 Video class header
 ************************************************************/

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/ImageSet/ImageSet.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <string>

namespace cv {
class VideoCapture;
}

namespace AnnotatorLib {

/************************************************************/
/**
 * @brief The Video class
 * represents an image set from a video file
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
  virtual ImageSetType getType() override;

  /**
   * @brief getImage
   * @param position the position to get, 0 based index
   * @return image at given position
   */
  virtual Image getImage(unsigned long position) override;

  virtual std::string getImagePath(unsigned long /*in*/ frame) override;

  bool gotoPosition(unsigned long position) override;

  long getPosition() override;

  /**
   * @brief hasNext
   * @return true if index greater than size
   */
  virtual bool hasNext() override;

  /**
   *
   * @return image at next index
   */
  virtual Image next() override;

  /**
   *
   * @return size
   */
  virtual unsigned int size() override;

  virtual unsigned int getFPS() override;

  virtual std::string getPath() override;

  virtual bool equals(ImageSet *other) override;

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
