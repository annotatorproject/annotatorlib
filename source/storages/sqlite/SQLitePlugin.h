// Copyright 2017 Annotator Team

#ifndef SQLITEPLUGIN_H
#define SQLITEPLUGIN_H

#include <AnnotatorLib/Storage/StoragePlugin.h>

class SQLitePlugin : public AnnotatorLib::Storage::StoragePlugin {
 public:
  SQLitePlugin();

  virtual const std::string name() { return "sqlite"; }
  virtual const std::string description() { return "SQLite Storage"; }

  virtual bool hasLoader();
  virtual bool hasSaver();
  virtual bool hasStorage();

  virtual shared_ptr<AnnotatorLib::Storage::AbstractLoader> createLoader();
  virtual shared_ptr<AnnotatorLib::Storage::AbstractSaver> createSaver();
  virtual shared_ptr<AnnotatorLib::Storage::AbstractStorage> createStorage();
};

#endif  // MONGODBPLUGIN_H
