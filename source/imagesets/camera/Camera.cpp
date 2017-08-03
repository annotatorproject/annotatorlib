// Copyright 2016 Annotator Team

#define Annotator_AnnotatorLib_Camera_BODY

/************************************************************
 ImageFolder class body
 ************************************************************/

// include associated header file
#include <opencv2/opencv.hpp>
#include <set>

#include "Camera.h"

// Derived includes directives

namespace AnnotatorLib {
namespace ImageSet {

Camera::Camera(std::string path) {
  this->path = path;
  initCamera();
}

ImageSetType Camera::getType() { return ImageSetType::CAMERA; }

Image Camera::getImage(unsigned long) { return next(); }

std::string Camera::getImagePath(unsigned long) { return ""; }

bool Camera::gotoPosition(unsigned long) { return true; }

long Camera::getPosition() { return 0; }

bool Camera::hasNext() { return capture.isOpened(); }

Image Camera::next() {
  Image img;
  if (capture.isOpened()) {
    capture >> img;
  }
  return img;
}

unsigned int Camera::size() { return 1; }

unsigned int Camera::getFPS() { return capture.get(CV_CAP_PROP_FPS); }

std::string Camera::getPath() { return path; }

bool Camera::equals(std::shared_ptr<AbstractImageSet> other) {
  if (this == other.get()) return true;
  if (other->getType() != ImageSetType::IMAGEFOLDER) return false;
  if (this->getPath() != other->getPath()) return false;
  return true;
}

void Camera::initCamera() { capture.open(0); }

// static attributes (if any)
}  // of namespace ImageSet
}  // of namespace AnnotatorLib

/************************************************************
 End of ImageFolder class body
 ************************************************************/
