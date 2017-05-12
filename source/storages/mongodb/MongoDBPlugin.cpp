#include "MongoDBPlugin.h"
#include "MongoDBLoader.h"
#include "MongoDBStorage.h"

#include <Poco/ClassLibrary.h>

MongoDBPlugin::MongoDBPlugin()
{

}

bool MongoDBPlugin::hasLoader()
{
    return true;
}

bool MongoDBPlugin::hasSaver()
{
    return false;
}

bool MongoDBPlugin::hasStorage()
{
    return true;
}

shared_ptr<AnnotatorLib::Loader::AbstractLoader> MongoDBPlugin::createLoader()
{
    return std::make_shared<MongoDBLoader>();
}

shared_ptr<AnnotatorLib::Saver::AbstractSaver> MongoDBPlugin::createSaver()
{
    return nullptr;
}

shared_ptr<AnnotatorLib::Storage::AbstractStorage> MongoDBPlugin::createStorage()
{
    return std::make_shared<MongoDBStorage>();
}

ANNOTATORLIB_API POCO_BEGIN_MANIFEST(AnnotatorLib::Storage::StoragePlugin)
    POCO_EXPORT_CLASS(MongoDBPlugin) POCO_END_MANIFEST
