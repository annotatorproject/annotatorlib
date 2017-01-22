// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_JSONLOADER_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_JSONLOADER_H

/************************************************************
 JSONLoader class header
 ************************************************************/
#include <AnnotatorLib/Loader/AbstractLoader.h>
#include <AnnotatorLib/Loader/Pkg_Loader.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <Poco/JSON/Object.h>

namespace AnnotatorLib {

class Session;
class Attribute;

namespace Loader {

/************************************************************/
/**
 * @brief The JSONLoader class
 * loads session from json file format.
 */
class ANNOTATORLIB_API JSONLoader : public AbstractLoader {
  // AbstractLoader interface
 public:
  void setPath(std::string path);
  StorageType getType();
  void loadSession(AnnotatorLib::Session *session);

 protected:
  std::string path;

  std::shared_ptr<AnnotatorLib::Attribute> loadAttribute(
      Poco::JSON::Object::Ptr value);

  void loadAttributes(Poco::JSON::Object::Ptr json,
                      AnnotatorLib::Session *session);
  void loadAnnotations(Poco::JSON::Object::Ptr json,
                       AnnotatorLib::Session *session);
  void loadClasses(Poco::JSON::Object::Ptr json,
                   AnnotatorLib::Session *session);
  void loadObjects(Poco::JSON::Object::Ptr json,
                   AnnotatorLib::Session *session);
  void loadFrames(Poco::JSON::Object::Ptr json, AnnotatorLib::Session *session);
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of JSONLoader class header
 ************************************************************/

#endif
