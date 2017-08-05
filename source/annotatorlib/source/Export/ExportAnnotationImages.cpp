// Copyright 2017 Annotator Team

#define Annotator_AnnotatorLib_ExportAnnotationImages_BODY

/************************************************************
 ImageFolder class body
 ************************************************************/

// include associated header file

#include "AnnotatorLib/Export/ExportAnnotationImages.h"

#include <set>
#include <stdexcept>

#include <opencv2/opencv.hpp>

// Derived includes directives

namespace AnnotatorLib {
namespace Export {

ExportAnnotationImages::ExportAnnotationImages(std::string path) {
  this->path = path;
}

std::string ExportAnnotationImages::getType() { return "annotationimages"; }

bool ExportAnnotationImages::equals(std::shared_ptr<AbstractExport> other) {
  if (this == other.get()) return true;
  if (other->getType() != this->getType()) return false;
  if (this->getPath() != other->getPath()) return false;
  return true;
}

std::string ExportAnnotationImages::getPath() { return path; }

// static attributes (if any)
}  // of namespace Export
}  // of namespace AnnotatorLib

/************************************************************
 End of ExportAnnotationImages class body
 ************************************************************/
