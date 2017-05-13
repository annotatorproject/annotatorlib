// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Storage_StorageFactory_BODY

/************************************************************
 LoaderFactory class body
 ************************************************************/

#include "AnnotatorLib/Storage/StorageFactory.h"
#include "AnnotatorLib/Storage/JSONStorage.h"
#include "AnnotatorLib/Storage/MySQLStorage.h"
#include "AnnotatorLib/Storage/SQLiteStorage.h"
#include "AnnotatorLib/Storage/XMLStorage.h"

#include <memory>

#include <Poco/ClassLoader.h>
#include <Poco/Manifest.h>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

namespace AnnotatorLib {
namespace Storage {

typedef Poco::ClassLoader<StoragePlugin> PLoader;
typedef Poco::Manifest<StoragePlugin> PManifest;

shared_ptr<AbstractStorage> StorageFactory::createStorage(std::string type) {
  if ("xml" == type) return createStorage(AnnotatorLib::StorageType::XML);
  if ("json" == type) return createStorage(AnnotatorLib::StorageType::JSON);
  if ("mysql" == type) return createStorage(AnnotatorLib::StorageType::MYSQL);
  if ("sqlite" == type) return createStorage(AnnotatorLib::StorageType::SQLITE);
  if ("mongodb" == type)
    return createStorage(AnnotatorLib::StorageType::MONGODB);
  return createStorage(AnnotatorLib::StorageType::UNKNOWN);
}

shared_ptr<AbstractStorage> StorageFactory::createStorage(
    AnnotatorLib::StorageType type) {
  switch (type) {
    case StorageType::XML:
      return std::make_shared<XMLStorage>();
    case StorageType::JSON:
      return std::make_shared<JSONStorage>();
    case StorageType::MYSQL:
      return std::make_shared<MySQLStorage>();
    case StorageType::SQLITE:
      return std::make_shared<SQLiteStorage>();
    //    case StorageType::MONGODB:
    //      return std::make_shared<MongoDBStorage>();
    default:
      return nullptr;
  }
}

void StorageFactory::loadPlugins(std::string dir) {
  boost::filesystem::path pluginsDir(dir);
  if (!boost::filesystem::exists(pluginsDir)) return;
  PLoader loader;

  boost::filesystem::directory_iterator dit(pluginsDir), eod;
  BOOST_FOREACH (boost::filesystem::path const &p, std::make_pair(dit, eod)) {
    if (boost::filesystem::is_regular_file(p)) {
      // skip non library files
      if (!(p.extension().string() == Poco::SharedLibrary::suffix())) continue;
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
    }
  }
}

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of LoaderFactory class body
 ************************************************************/
