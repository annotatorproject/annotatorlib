// Copyright 2017 Annotator Team

#ifndef VIDEOPLUGIN_H
#define VIDEOPLUGIN_H

#include <AnnotatorLib/ImageSet/ImageSetPlugin.h>

class VideoPlugin : public AnnotatorLib::ImageSet::ImageSetPlugin {
 public:
  VideoPlugin();

  virtual const std::string name() override { return "camera"; }
  virtual const std::string description() override { return "Camera Image Set"; }

  virtual std::shared_ptr<AnnotatorLib::ImageSet::AbstractImageSet> create(std::string path) override;
};

#endif  // VIDEOPLUGIN_H
