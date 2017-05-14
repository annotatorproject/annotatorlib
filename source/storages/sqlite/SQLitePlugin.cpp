// Copyright 2017 Annotator Team

#include "SQLitePlugin.h"
#include "SQLiteLoader.h"
#include "SQLiteSaver.h"
#include "SQLiteStorage.h"

#include <Poco/ClassLibrary.h>

SQLitePlugin::SQLitePlugin() {}

bool SQLitePlugin::hasLoader() { return true; }

bool SQLitePlugin::hasSaver() { return false; }

bool SQLitePlugin::hasStorage() { return true; }

shared_ptr<AnnotatorLib::Storage::AbstractLoader> SQLitePlugin::createLoader() {
  return std::make_shared<SQLiteLoader>();
}

shared_ptr<AnnotatorLib::Storage::AbstractSaver> SQLitePlugin::createSaver() {
  return std::make_shared<SQLiteSaver>();
}

shared_ptr<AnnotatorLib::Storage::AbstractStorage>
SQLitePlugin::createStorage() {
  return std::make_shared<SQLiteStorage>();
}

ANNOTATORLIB_API POCO_BEGIN_MANIFEST(AnnotatorLib::Storage::StoragePlugin)
    POCO_EXPORT_CLASS(SQLitePlugin) POCO_END_MANIFEST
