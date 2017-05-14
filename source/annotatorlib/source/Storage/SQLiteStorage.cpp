// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Storage_SQLiteStorage_BODY

/************************************************************
 SQLiteStorage class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/Storage/SQLiteLoader.h>
#include <AnnotatorLib/Storage/SQLiteSaver.h>
#include <AnnotatorLib/Storage/SQLiteStorage.h>

#include <Poco/Data/RecordSet.h>
#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/Statement.h>

using Poco::Data::Session;
using Poco::Data::Statement;
using namespace Poco::Data::Keywords;

namespace AnnotatorLib {
namespace Storage {

void SQLiteStorage::setPath(std::string path) { this->path = path; }

StorageType SQLiteStorage::getType() {
  return AnnotatorLib::StorageType::SQLITE;
}

SQLiteStorage::~SQLiteStorage() {}

bool SQLiteStorage::open() {
  Poco::Data::SQLite::Connector::registerConnector();
  pool = new Poco::Data::SessionPool("SQLite", this->path);
  createTables();

  AnnotatorLib::Storage::SQLiteLoader loader;
  loader.setPath(this->path);
  loader.loadSession(this);

  this->_open = true;
  return _open;
}

void SQLiteStorage::createTables() {
  Poco::Data::Statement statement = getStatement();

  statement = getStatement();

  // statement << "PRAGMA encoding = \"UTF-8\";";
  // statement.execute();

  statement << "CREATE TABLE IF NOT EXISTS `annotations` ( \
           `id` INTEGER NOT NULL, \
            `next` INTEGER NOT NULL, \
            `previous` INTEGER NOT NULL, \
            `object` INTEGER NOT NULL, \
            `frame` INTEGER NOT NULL, \
            `x` REAL NOT NULL DEFAULT 0, \
            `y` REAL NOT NULL DEFAULT 0, \
           `width` REAL NOT NULL DEFAULT 1, \
            `height` REAL NOT NULL DEFAULT 1, \
            `type` TEXT NOT NULL, \
            PRIMARY KEY (`id`) \
            );";
  statement.execute();
  /*
    statement = getStatement();

    statement << "CREATE TABLE IF NOT EXISTS `classes` ("
              << "`id` INTEGER NOT NULL, "
              << "`name` TEXT NOT NULL,"
              << "PRIMARY KEY (`id`)"
              << ");";
    statement.execute();

    statement = getStatement();

    statement << "CREATE TABLE IF NOT EXISTS `objects` ("
              << "`id` INTEGER NOT NULL, "
              << "`name` TEXT NOT NULL,"
              << "`class` INTEGER NOT NULL,"
              << "PRIMARY KEY (`id`)"
              << ");";
    statement.execute();*/
}

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of SQLiteStorage class body
 ************************************************************/
