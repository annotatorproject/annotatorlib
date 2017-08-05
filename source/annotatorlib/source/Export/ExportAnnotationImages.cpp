// Copyright 2017 Annotator Team

#define Annotator_AnnotatorLib_ExportAnnotationImages_BODY

/************************************************************
 ExportAnnotationImages class body
 ************************************************************/

// include associated header file

#include <experimental/filesystem>

#include "AnnotatorLib/Annotation.h"
#include "AnnotatorLib/Export/ExportAnnotationImages.h"

#include <set>
#include <stdexcept>

#include <opencv2/opencv.hpp>

// Derived includes directives

namespace fs = std::experimental::filesystem;

namespace AnnotatorLib {
namespace Export {

ExportAnnotationImages::ExportAnnotationImages(std::shared_ptr<Project> project,
                                               std::string path) {
  this->project = project;
  this->path = path;
}

std::string ExportAnnotationImages::getType() { return "annotationimages"; }

bool ExportAnnotationImages::equals(std::shared_ptr<AbstractExport> other) {
  if (this == other.get()) return true;
  if (other->getType() != this->getType()) return false;
  if (this->getPath() != other->getPath()) return false;
  return true;
}

void ExportAnnotationImages::exportClass(std::shared_ptr<Class> theClass) {
  std::string classPath = path + "/" + theClass->getName();
}

void ExportAnnotationImages::exportObject(std::shared_ptr<Object> object) {
  std::string classPath = path + "/" + object->getClass()->getName() + "/";
  if (!fs::exists(classPath)) {
    fs::create_directory(classPath);
  }
  std::string objectPath = classPath + object->getName() + "_";
  for (auto annotation : object->getAnnotations()) {
    unsigned long frame =
        annotation.second.lock()->getFrame()->getFrameNumber();
    cv::Mat tmp = project->getImageSet()->getImage(frame);
    float x = std::max(annotation.second.lock()->getX(), 0.f);
    float y = std::max(annotation.second.lock()->getY(), 0.f);
    float w = std::min(annotation.second.lock()->getWidth(), tmp.cols - x);
    float h = std::min(annotation.second.lock()->getHeight(), tmp.rows - y);

    cv::Rect rect(x, y, w, h);

    cv::Mat cropped;
    tmp(rect).copyTo(cropped);
    std::string imagePath = objectPath + std::to_string(frame) + ".jpg";
    cv::imwrite(imagePath, cropped);
  }
}

std::string ExportAnnotationImages::getPath() { return path; }

void ExportAnnotationImages::doExport() {
  for (auto object : project->getSession()->getObjects()) {
    exportObject(object.second);
  }
}

// static attributes (if any)
}  // of namespace Export
}  // of namespace AnnotatorLib

/************************************************************
 End of ExportAnnotationImages class body
 ************************************************************/
