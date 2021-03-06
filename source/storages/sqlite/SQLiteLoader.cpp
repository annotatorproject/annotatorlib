// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Loader_SQLiteLoader_BODY

/************************************************************
 SQLiteLoader class body
 ************************************************************/

// include associated header file
#include "SQLiteLoader.h"

#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

#include <Poco/Data/RecordSet.h>
#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Data/SessionPool.h>
#include <Poco/Data/Statement.h>
#include <Poco/Tuple.h>

using std::shared_ptr;
using namespace Poco::Data::Keywords;

AnnotatorLib::StorageType SQLiteLoader::getType() {
  return AnnotatorLib::StorageType::SQLITE;
}

void SQLiteLoader::loadSession(AnnotatorLib::Session *session) {
  Poco::Data::SQLite::Connector::registerConnector();
  Poco::Data::SessionPool pool("SQLite", this->path);

  Poco::Data::Session sess(pool.get());

  loadAttributes(sess, session);
  loadClasses(sess, session);
  loadObjects(sess, session);
  loadFrames(sess, session);
  loadAnnotations(sess, session);
}

/************************************************************
 End of SQLiteLoader class body
 ************************************************************/
