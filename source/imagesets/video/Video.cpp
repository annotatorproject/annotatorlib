// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Video_BODY

/************************************************************
 Video class body
 ************************************************************/

// include associated header file
#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Video.h"

// Derived includes directives

namespace AnnotatorLib {
namespace ImageSet {

Video::Video(std::string path) {
  this->path = path;
  initCapture();
}

Video::~Video() {
  if (capture != nullptr) delete capture;
}

ImageSetType Video::getType() { return ImageSetType::VIDEO; }

Image Video::getImage(unsigned long position) {
  long prev = getPosition();
  gotoPosition(position - 1);
  Image img = next();
  gotoPosition(prev);
  return img;
}

std::string Video::getImagePath(unsigned long frame) { return ""; }

bool Video::gotoPosition(unsigned long position) {
  return capture->set(CV_CAP_PROP_POS_FRAMES, position);
}

long Video::getPosition() { return capture->get(CV_CAP_PROP_POS_FRAMES); }

bool Video::hasNext() {
  return capture->get(CV_CAP_PROP_POS_FRAMES) <
         capture->get(CV_CAP_PROP_FRAME_COUNT);
}

Image Video::next() {
  cv::Mat frame;
  capture->read(frame);
  Image img = frame;
  return img;
}

unsigned int Video::size() { return capture->get(CV_CAP_PROP_FRAME_COUNT); }

unsigned int Video::getFPS() { return capture->get(CV_CAP_PROP_FPS); }

std::string Video::getPath() { return this->path; }

bool Video::equals(std::shared_ptr<AbstractImageSet> other) {
  if (this == other.get()) return true;
  // if(other == nullptr)
  //    return false;
  if (other->getType() != ImageSetType::VIDEO) return false;
  if (this->getPath() != other->getPath()) return false;
  return true;
}

void Video::initCapture() { capture = new cv::VideoCapture(path); }

// static attributes (if any)
}  // of namespace ImageSet
}  // of namespace AnnotatorLib

/************************************************************
 End of Video class body
 ************************************************************/
