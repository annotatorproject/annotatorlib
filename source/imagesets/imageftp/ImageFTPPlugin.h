// Copyright 2017 Annotator Team

#ifndef IMAGEFTPPLUGIN_H
#define IMAGEFTPPLUGIN_H

#include <AnnotatorLib/ImageSet/ImageSetPlugin.h>

class ImageFTPPlugin : public AnnotatorLib::ImageSet::ImageSetPlugin {
 public:
  ImageFTPPlugin();

  virtual const std::string name() override{ return "imageftp"; }
  virtual const std::string description() override{ return "Image FTP Image Set"; }

  virtual std::shared_ptr<AnnotatorLib::ImageSet::AbstractImageSet> create(std::string path) override;
};

#endif  // IMAGEFTPPLUGIN_H
