// Copyright 2017 Annotator Team

#include "MySQLPlugin.h"
#include "MySQLLoader.h"
#include "MySQLSaver.h"
#include "MySQLStorage.h"

#include <Poco/ClassLibrary.h>

MySQLPlugin::MySQLPlugin() {}

bool MySQLPlugin::hasLoader() { return true; }

bool MySQLPlugin::hasSaver() { return false; }

bool MySQLPlugin::hasStorage() { return true; }

shared_ptr<AnnotatorLib::Storage::AbstractLoader> MySQLPlugin::createLoader() {
  return std::make_shared<MySQLLoader>();
}

shared_ptr<AnnotatorLib::Storage::AbstractSaver> MySQLPlugin::createSaver() {
  return std::make_shared<MySQLSaver>();
}

shared_ptr<AnnotatorLib::Storage::AbstractStorage>
MySQLPlugin::createStorage() {
  return std::make_shared<MySQLStorage>();
}

ANNOTATORLIB_API POCO_BEGIN_MANIFEST(AnnotatorLib::Storage::StoragePlugin)
    POCO_EXPORT_CLASS(MySQLPlugin) POCO_END_MANIFEST
