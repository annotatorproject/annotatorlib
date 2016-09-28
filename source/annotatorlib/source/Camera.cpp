// Copyright 2016 Annotator Team

#define Annotator_AnnotatorLib_Camera_BODY

/************************************************************
 ImageFolder class body
 ************************************************************/

// include associated header file
#include <opencv2/opencv.hpp>
#include <set>

#include "AnnotatorLib/Camera.h"

// Derived includes directives

namespace AnnotatorLib {

Camera::Camera(std::string path) {
  this->path = path;
  initCamera();
}

ImageSetType Camera::getType() { return ImageSetType::CAMERA; }

Image Camera::getImage(unsigned long frame) { return next(); }

bool Camera::gotoPosition(unsigned long position) { return true; }

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

std::string Camera::getPath() { return path; }

bool Camera::equals(ImageSet *other) {
  if (this == other) return true;
  if (other->getType() != ImageSetType::IMAGEFOLDER) return false;
  if (this->getPath() != other->getPath()) return false;
  return true;
}

void Camera::initCamera() { capture.open(0); }

// static attributes (if any)

}  // of namespace AnnotatorLib

/************************************************************
 End of ImageFolder class body
 ************************************************************/
