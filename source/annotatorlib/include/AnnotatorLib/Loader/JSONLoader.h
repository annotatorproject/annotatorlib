// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_JSONLOADER_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_JSONLOADER_H

/************************************************************
 JSONLoader class header
 ************************************************************/
#include <AnnotatorLib/Loader/Pkg_Loader.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include <QJsonObject>

#include <AnnotatorLib/Loader/AbstractLoader.h>

namespace AnnotatorLib {

class Session;

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

  void loadAttributes(QJsonObject &json, AnnotatorLib::Session *session);
  void loadAnnotations(QJsonObject &json, AnnotatorLib::Session *session);
  void loadClasses(QJsonObject &json, AnnotatorLib::Session *session);
  void loadObjects(QJsonObject &json, AnnotatorLib::Session *session);
  void loadFrames(QJsonObject &json, AnnotatorLib::Session *session);

  void loadAnnotationsNextPrevious(QJsonObject &json,
                                   AnnotatorLib::Session *session);
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
