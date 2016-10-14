// Copyright 2016 Annotator Team

#define Annotator_AnnotatorLib_ImageFolder_BODY

/************************************************************
 ImageFolder class body
 ************************************************************/

// include associated header file
#include <opencv2/opencv.hpp>
#include <set>

#include "AnnotatorLib/ImageFolder.h"

// Derived includes directives

namespace AnnotatorLib {

const std::set<std::string> imagetypes = {(".bmp"), (".pbm"),  (".pgm"),
                                          (".ppm"), (".jpg"),  (".jpeg"),
                                          (".png"), (".tiff"), (".tif")};

ImageFolder::ImageFolder(std::string path) {
  this->path = path;
  loadFolder();
}

ImageSetType ImageFolder::getType() { return ImageSetType::IMAGEFOLDER; }

Image ImageFolder::getImage(unsigned long frame) {
  Image img;
  try {
    img =
        cv::imread((images.begin() + frame - 1)->string(), CV_LOAD_IMAGE_COLOR);
  } catch (std::exception &e) {
  }
  return img;
}

bool ImageFolder::gotoPosition(unsigned long position) {
  if (images.size() < position) return false;
  this->position = position;
  imgIter = images.begin() + position;
  return true;
}

long ImageFolder::getPosition() { return position; }

bool ImageFolder::hasNext() { return imgIter != images.end(); }

Image ImageFolder::next() {
  Image img;
  try {
    img = cv::imread(imgIter->string(), CV_LOAD_IMAGE_COLOR);
    imgIter++;
    position++;
  } catch (std::exception &e) {
  }
  return img;
}

unsigned int ImageFolder::size() { return images.size(); }

std::string ImageFolder::getPath() { return path; }

bool ImageFolder::equals(ImageSet *other) {
  if (this == other) return true;
  if (other->getType() != ImageSetType::IMAGEFOLDER) return false;
  if (this->getPath() != other->getPath()) return false;
  return true;
}

struct sort_functor {
  bool operator()(const std::string &a, const std::string &b) { return a < b; }
};

void ImageFolder::loadFolder() {
  if (boost::filesystem::exists(this->path)) {
    for (boost::filesystem::directory_iterator it(this->path);
         it != boost::filesystem::directory_iterator(); ++it) {
      if (imagetypes.find(it->path().extension().string()) == imagetypes.end())
        continue;

      images.push_back(*it);
    }
    std::sort(images.begin(), images.end());
    imgIter = images.begin();
  }
}

// static attributes (if any)

}  // of namespace AnnotatorLib

/************************************************************
 End of ImageFolder class body
 ************************************************************/
