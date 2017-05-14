// Copyright 2017 Annotator Team

#ifndef MYSQLPLUGIN_H
#define MYSQLPLUGIN_H

#include <AnnotatorLib/Storage/StoragePlugin.h>

class MySQLPlugin : public AnnotatorLib::Storage::StoragePlugin {
 public:
  MySQLPlugin();

  virtual const std::string name() { return "mysql"; }
  virtual const std::string description() { return "MySQL Storage"; }

  virtual bool hasLoader();
  virtual bool hasSaver();
  virtual bool hasStorage();

  virtual shared_ptr<AnnotatorLib::Storage::AbstractLoader> createLoader();
  virtual shared_ptr<AnnotatorLib::Storage::AbstractSaver> createSaver();
  virtual shared_ptr<AnnotatorLib::Storage::AbstractStorage> createStorage();
};

#endif  // MYSQLPLUGIN_H
