// Copyright 2017 Annotator Team

#define Annotator_AnnotatorLib_ExportFactory_BODY

/************************************************************
 ExportFactory class body
 ************************************************************/

#include "AnnotatorLib/Export/ExportFactory.h"
#include "AnnotatorLib/Export/ExportAnnotationImages.h"

#include <stdexcept>
#include <string>

#include <Poco/ClassLoader.h>
#include <Poco/Manifest.h>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

namespace AnnotatorLib {
namespace Export {

// static attributes (if any)

typedef Poco::ClassLoader<ExportPlugin> PLoader;
typedef Poco::Manifest<ExportPlugin> PManifest;

static ExportFactory *_instance = nullptr;

/**
 *
 * @param type
 * @return imageSet
 */
std::shared_ptr<AbstractExport> ExportFactory::createExport(
    std::string type, std::string path) {
  if ("annotationimages" == type)
    return std::make_shared<ExportAnnotationImages>(path);

  std::shared_ptr<ExportPlugin> plugin = this->plugins[type];
  if (plugin) return plugin->create(path);
  throw std::invalid_argument("ExportType unknown!");
}

std::list<std::string> ExportFactory::availableImageSets() {
  return _availableExports;
}

void ExportFactory::loadPlugins(std::string dir) {
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
      ExportPlugin *plugin = itMan->create();
      std::shared_ptr<ExportPlugin> sharedPlugin(plugin);
      plugins.insert(plugins.begin(),
                     std::pair<std::string, std::shared_ptr<ExportPlugin>>(
                         plugin->name(), sharedPlugin));
      addAvailableExport(plugin);
    }
  }
}

ExportFactory *ExportFactory::instance() {
  if (!_instance) _instance = new ExportFactory();
  return _instance;
}

ExportFactory::~ExportFactory() { _instance = nullptr; }

void ExportFactory::addAvailableExport(ExportPlugin *plugin) {
  if (plugin) {
    bool found =
        (std::find(_availableExports.begin(), _availableExports.end(),
                   plugin->name()) != _availableExports.end());
    if (!found)
      _availableExports.insert(_availableExports.end(), plugin->name());
  }
}

}  // of namespace Export
}  // of namespace AnnotatorLib

/************************************************************
 End of ExportFactory class body
 ************************************************************/
