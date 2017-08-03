// Copyright 2017 Annotator Team

#include "ImageFTPPlugin.h"
#include "ImageFTP.h"

#include <Poco/ClassLibrary.h>

ImageFTPPlugin::ImageFTPPlugin() {}

std::shared_ptr<AnnotatorLib::ImageSet::AbstractImageSet>
ImageFTPPlugin::create(std::string path) {
  return std::make_shared<AnnotatorLib::ImageSet::ImageFTP>(path);
}

ANNOTATORLIB_API POCO_BEGIN_MANIFEST(AnnotatorLib::ImageSet::ImageSetPlugin)
    POCO_EXPORT_CLASS(ImageFTPPlugin) POCO_END_MANIFEST
