// Copyright 2016-2017 Annotator Team

#define Annotator_AnnotatorLib_ImageSetFactory_BODY

/************************************************************
 ImageSetFactory class body
 ************************************************************/

#include "AnnotatorLib/ImageSet/ImageSetFactory.h"
#include "AnnotatorLib/ImageSet/ImageFolder.h"

#include <stdexcept>
#include <string>

#include <Poco/ClassLoader.h>
#include <Poco/Manifest.h>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

namespace AnnotatorLib {
namespace ImageSet {

// static attributes (if any)

typedef Poco::ClassLoader<ImageSetPlugin> PLoader;
typedef Poco::Manifest<ImageSetPlugin> PManifest;

static ImageSetFactory *_instance;

/**
 *
 * @param type
 * @return imageSet
 */
std::shared_ptr<AbstractImageSet> ImageSetFactory::createImageSet(
    std::string type, std::string path) {
  if ("images" == type || "imagefolder" == type)
    return std::make_shared<ImageFolder>(path);

  std::shared_ptr<ImageSetPlugin> plugin = this->plugins[type];
  if (plugin) return plugin->create(path);
  throw std::invalid_argument("ImageSetType unknown!");
}

std::list<std::string> ImageSetFactory::availableImageSets() {
  return _availableImageSets;
}

void ImageSetFactory::loadPlugins(std::string dir) {
  boost::filesystem::path pluginsDir(dir);
  if (!boost::filesystem::exists(pluginsDir)) return;
  PLoader loader;

  boost::filesystem::directory_iterator dit(pluginsDir), eod;
  BOOST_FOREACH (boost::filesystem::path const &p, std::make_pair(dit, eod)) {
    if (boost::filesystem::is_regular_file(p)) {
      // skip non library files
      // if (!(p.extension().string() == Poco::SharedLibrary::suffix()))
      // continue;
      std::string fileName = boost::filesystem::absolute(p).string();
      try {
        loader.loadLibrary(fileName);
      } catch (Poco::Exception &e) {
      }
    }
  }

  PLoader::Iterator it(loader.begin());
  PLoader::Iterator end(loader.end());
  for (; it != end; ++it) {
    PManifest::Iterator itMan(it->second->begin());
    PManifest::Iterator endMan(it->second->end());
    for (; itMan != endMan; ++itMan) {
      ImageSetPlugin *plugin = itMan->create();
      std::shared_ptr<ImageSetPlugin> sharedPlugin(plugin);
      plugins.insert(plugins.begin(),
                     std::pair<std::string, std::shared_ptr<ImageSetPlugin>>(
                         plugin->name(), sharedPlugin));
      addAvailableImageSet(plugin);
    }
  }
}

ImageSetFactory *ImageSetFactory::instance() {
  if (!_instance) _instance = new ImageSetFactory();
  return _instance;
}

ImageSetFactory::~ImageSetFactory() { _instance = nullptr; }

void ImageSetFactory::addAvailableImageSet(ImageSetPlugin *plugin) {
  if (plugin) {
    bool found =
        (std::find(_availableImageSets.begin(), _availableImageSets.end(),
                   plugin->name()) != _availableImageSets.end());
    if (!found)
      _availableImageSets.insert(_availableImageSets.end(), plugin->name());
  }
}

}  // of namespace ImageSet
}  // of namespace AnnotatorLib

/************************************************************
 End of ImageSetFactory class body
 ************************************************************/
