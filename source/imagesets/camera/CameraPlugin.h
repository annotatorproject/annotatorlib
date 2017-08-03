// Copyright 2017 Annotator Team

#ifndef CAMERAPLUGIN_H
#define CAMERAPLUGIN_H

#include <AnnotatorLib/ImageSet/ImageSetPlugin.h>

class CameraPlugin : public AnnotatorLib::ImageSet::ImageSetPlugin {
 public:
  CameraPlugin();

  virtual const std::string name() override { return "camera"; }
  virtual const std::string description() override { return "Camera Image Set"; }

  virtual std::shared_ptr<AnnotatorLib::ImageSet::AbstractImageSet> create(std::string path) override;
};

#endif  // CAMERAPLUGIN_H
