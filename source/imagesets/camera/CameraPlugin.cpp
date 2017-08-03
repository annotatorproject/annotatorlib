// Copyright 2017 Annotator Team

#include "CameraPlugin.h"
#include "Camera.h"

#include <Poco/ClassLibrary.h>

CameraPlugin::CameraPlugin() {}

std::shared_ptr<AnnotatorLib::ImageSet::AbstractImageSet>
CameraPlugin::create(std::string path) {
  return std::make_shared<AnnotatorLib::ImageSet::Camera>(path);
}

ANNOTATORLIB_API POCO_BEGIN_MANIFEST(AnnotatorLib::ImageSet::ImageSetPlugin)
    POCO_EXPORT_CLASS(CameraPlugin) POCO_END_MANIFEST
