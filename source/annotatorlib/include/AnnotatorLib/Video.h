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
  virtual ImageSetType getType();

  /**
   * @brief getImage
   * @param position the position to get, 0 based index
   * @return image at given position
   */
  virtual Image getImage(unsigned long position) override;

  bool gotoPosition(unsigned long position) override;

  long getPosition() override;

  /**
   * @brief hasNext
   * @return true if index greater than size
   */
  virtual bool hasNext();

  /**
   *
   * @return image at next index
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
