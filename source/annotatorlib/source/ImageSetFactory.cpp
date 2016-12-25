// Copyright 2016 Annotator Team

#define Annotator_AnnotatorLib_ImageSetFactory_BODY

/************************************************************
 ImageSetFactory class body
 ************************************************************/
#include <stdexcept>
#include <string>
// include associated header file
#include "AnnotatorLib/Camera.h"
#include "AnnotatorLib/ImageFTP.h"
#include "AnnotatorLib/ImageFolder.h"
#include "AnnotatorLib/ImageSetFactory.h"
#include "AnnotatorLib/Video.h"

// Derived includes directives

namespace AnnotatorLib {

// static attributes (if any)

/**
 *
 * @param type
 * @return imageSet
 */
ImageSet *ImageSetFactory::createImageSet(ImageSetType type, std::string path) {
  if (type == ImageSetType::CAMERA) return new Camera(path);
  if (type == ImageSetType::VIDEO) return new Video(path);
  if (type == ImageSetType::IMAGEFOLDER) return new ImageFolder(path);
  if (type == ImageSetType::IMAGEFTP) return new ImageFTP(path);
  throw std::invalid_argument("ImageSetType unknown!");
}

/**
 *
 * @param type
 * @return imageSet
 */
ImageSet *ImageSetFactory::createImageSet(std::string type, std::string path) {
  ImageSetType t;
  if (type == "camera") t = ImageSetType::CAMERA;
  if (type == "video") t = ImageSetType::VIDEO;
  if (type == "images") t = ImageSetType::IMAGEFOLDER;
  if (type == "imageftp") t = ImageSetType::IMAGEFTP;
  return createImageSet(t, path);
}

}  // of namespace AnnotatorLib

/************************************************************
 End of ImageSetFactory class body
 ************************************************************/
