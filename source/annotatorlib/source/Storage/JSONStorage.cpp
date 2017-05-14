// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Storage_JSONStorage_BODY

/************************************************************
 JSONStorage class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/Loader/JSONLoader.h>
#include <AnnotatorLib/Storage/JSONSaver.h>
#include <AnnotatorLib/Storage/JSONStorage.h>

// Derived includes directives

namespace AnnotatorLib {
namespace Storage {

void JSONStorage::setPath(std::string path) { this->path = path; }

StorageType JSONStorage::getType() { return AnnotatorLib::StorageType::JSON; }

bool JSONStorage::open() {
  AnnotatorLib::Loader::JSONLoader loader;
  loader.setPath(this->path);
  loader.loadSession(this);
  this->_open = true;
  return _open;
}

bool JSONStorage::isOpen() { return _open; }

bool JSONStorage::flush() {
  AnnotatorLib::Storage::JSONSaver saver;
  saver.setPath(this->path);
  saver.saveSession(this);
  _save = saver.close();
  return _save;
}

bool JSONStorage::isSaved() { return _save; }

bool JSONStorage::close() {
  this->_open = false;
  return flush();
}

// static attributes (if any)

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of JSONStorage class body
 ************************************************************/
