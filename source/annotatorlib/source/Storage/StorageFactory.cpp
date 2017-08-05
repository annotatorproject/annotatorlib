// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Storage_StorageFactory_BODY

/************************************************************
 LoaderFactory class body
 ************************************************************/

#include "AnnotatorLib/Storage/JSONLoader.h"
#include "AnnotatorLib/Storage/XMLLoader.h"

#include "AnnotatorLib/Storage/JSONSaver.h"
#include "AnnotatorLib/Storage/XMLSaver.h"

#include "AnnotatorLib/Storage/JSONStorage.h"
#include "AnnotatorLib/Storage/StorageFactory.h"
#include "AnnotatorLib/Storage/XMLStorage.h"

#include <algorithm>
#include <memory>

#include <Poco/ClassLoader.h>
#include <Poco/Manifest.h>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

namespace AnnotatorLib {
namespace Storage {

typedef Poco::ClassLoader<StoragePlugin> PLoader;
typedef Poco::Manifest<StoragePlugin> PManifest;

static StorageFactory *_instance = nullptr;

shared_ptr<AbstractStorage> StorageFactory::createStorage(std::string type) {
  if ("xml" == type) return std::make_shared<XMLStorage>();
  if ("json" == type) return std::make_shared<JSONStorage>();

  std::shared_ptr<StoragePlugin> plugin = this->plugins[type];
  if (plugin && plugin->hasStorage()) return plugin->createStorage();
  return nullptr;
}

std::list<std::string> StorageFactory::availableStorages() {
  return _availableStorages;
}

shared_ptr<Storage::AbstractLoader> StorageFactory::createLoader(
    std::string type) {
  if ("xml" == type)
    return std::make_shared<AnnotatorLib::Storage::XMLLoader>();
  if ("json" == type)
    return std::make_shared<AnnotatorLib::Storage::JSONLoader>();

  std::shared_ptr<StoragePlugin> plugin = this->plugins[type];
  if (plugin && plugin->hasLoader()) return plugin->createLoader();
  return nullptr;
}

std::list<std::string> StorageFactory::availableLoader() {
  return _availableLoader;
}

shared_ptr<Storage::AbstractSaver> StorageFactory::createSaver(
    std::string type) {
  if ("xml" == type) return std::make_shared<AnnotatorLib::Storage::XMLSaver>();
  if ("json" == type)
    return std::make_shared<AnnotatorLib::Storage::JSONSaver>();

  std::shared_ptr<StoragePlugin> plugin = this->plugins[type];
  if (plugin && plugin->hasSaver()) return plugin->createSaver();
  return nullptr;
}

std::list<std::string> StorageFactory::availableSaver() {
  return _availableSaver;
}

void StorageFactory::loadPlugins(std::string dir) {
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
      StoragePlugin *plugin = itMan->create();
      std::shared_ptr<StoragePlugin> sharedPlugin(plugin);
      plugins.insert(plugins.begin(),
                     std::pair<std::string, std::shared_ptr<StoragePlugin>>(
                         plugin->name(), sharedPlugin));
      addAvailableLoader(plugin);
      addAvailableSaver(plugin);
      addAvailableStorage(plugin);
    }
  }
}

StorageFactory *StorageFactory::instance() {
  if (!_instance) _instance = new StorageFactory();
  return _instance;
}

StorageFactory::~StorageFactory() { _instance = nullptr; }

void StorageFactory::addAvailableStorage(StoragePlugin *plugin) {
  if (plugin->hasStorage()) {
    bool found =
        (std::find(_availableStorages.begin(), _availableStorages.end(),
                   plugin->name()) != _availableStorages.end());
    if (!found)
      _availableStorages.insert(_availableStorages.end(), plugin->name());
  }
}

void StorageFactory::addAvailableLoader(StoragePlugin *plugin) {
  if (plugin->hasLoader()) {
    bool found = (std::find(_availableLoader.begin(), _availableLoader.end(),
                            plugin->name()) != _availableLoader.end());
    if (!found) _availableLoader.insert(_availableLoader.end(), plugin->name());
  }
}

void StorageFactory::addAvailableSaver(StoragePlugin *plugin) {
  if (plugin->hasSaver()) {
    bool found = (std::find(_availableSaver.begin(), _availableSaver.end(),
                            plugin->name()) != _availableSaver.end());
    if (!found) _availableSaver.insert(_availableSaver.end(), plugin->name());
  }
}

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of LoaderFactory class body
 ************************************************************/
