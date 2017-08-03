// Copyright 2017 Annotator Team

#include "VideoPlugin.h"
#include "Video.h"

#include <Poco/ClassLibrary.h>

VideoPlugin::VideoPlugin() {}

std::shared_ptr<AnnotatorLib::ImageSet::AbstractImageSet> VideoPlugin::create(
    std::string path) {
  return std::make_shared<AnnotatorLib::ImageSet::Video>(path);
}

ANNOTATORLIB_API POCO_BEGIN_MANIFEST(AnnotatorLib::ImageSet::ImageSetPlugin)
    POCO_EXPORT_CLASS(VideoPlugin) POCO_END_MANIFEST
