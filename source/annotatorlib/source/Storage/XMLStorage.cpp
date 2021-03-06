// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Storage_JSONStorage_BODY

/************************************************************
 JSONLoader class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/Storage/XMLLoader.h>
#include <AnnotatorLib/Storage/XMLSaver.h>
#include <AnnotatorLib/Storage/XMLStorage.h>

// Derived includes directives

namespace AnnotatorLib {
namespace Storage {

void XMLStorage::setPath(std::string path) { this->path = path; }

StorageType XMLStorage::getType() { return AnnotatorLib::StorageType::XML; }

bool XMLStorage::open() {
  AnnotatorLib::Storage::XMLLoader loader;
  loader.setPath(this->path);
  loader.loadSession(this);
  this->_open = true;
  return _open;
}

bool XMLStorage::isOpen() { return _open; }

bool XMLStorage::flush() {
  AnnotatorLib::Storage::XMLSaver saver;
  saver.setPath(this->path);
  saver.saveSession(this);
  _save = saver.close();
  return _save;
}

bool XMLStorage::isSaved() { return _save; }

bool XMLStorage::close() {
  this->_open = false;
  return flush();
}

// static attributes (if any)

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of JSONLoader class body
 ************************************************************/
