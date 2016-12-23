// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Storage_MySQLStorage_BODY

/************************************************************
 MySQLStorage class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/Loader/MySQLLoader.h>
#include <AnnotatorLib/Saver/MySQLSaver.h>
#include <AnnotatorLib/Storage/MySQLStorage.h>

// Derived includes directives

namespace AnnotatorLib {
namespace Storage {

void MySQLStorage::setPath(std::string path) { this->path = path; }

StorageType MySQLStorage::getType() { return AnnotatorLib::StorageType::MYSQL; }

bool MySQLStorage::open() {
  AnnotatorLib::Loader::MySQLLoader loader;
  loader.setPath(this->path);
  loader.loadSession(this);
  this->_open = true;
  return _open;
}

bool MySQLStorage::isOpen() { return _open; }

bool MySQLStorage::flush() {
  AnnotatorLib::Saver::MySQLSaver saver;
  saver.setPath(this->path);
  saver.saveSession(this);
  _save = saver.close();
  return _save;
}

bool MySQLStorage::isSaved() { return _save; }

bool MySQLStorage::close() {
  this->_open = false;
  return flush();
}

// static attributes (if any)

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of MySQLStorage class body
 ************************************************************/
