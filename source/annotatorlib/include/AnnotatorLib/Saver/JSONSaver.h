// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_SAVER_JSONSAVER_H
#define ANNOTATOR_ANNOTATORLIB_SAVER_JSONSAVER_H

/************************************************************
 JSONSaver class header
 ************************************************************/
#include <AnnotatorLib/Saver/Pkg_Saver.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include <QJsonObject>

#include <AnnotatorLib/Class.h>
#include <AnnotatorLib/Saver/AbstractSaver.h>

namespace AnnotatorLib {
namespace Saver {

/************************************************************/
/**
 * @brief The JSONSaver class
 * writes session to json file.
 */
class ANNOTATORLIB_API JSONSaver : public AbstractSaver {
  // AbstractSaver interface
 public:
  void saveAnnotation(const Annotation annotation);
  void setPath(std::string path);
  StorageType getType();
  void saveSession(const AnnotatorLib::Session* session);
  bool close();

 protected:
  std::string path;
  QJsonObject sessionToJson(const AnnotatorLib::Session* session);
  QJsonObject attributeToJson(
      const shared_ptr<AnnotatorLib::Attribute> attribute);
  QJsonObject annotationToJson(
      const shared_ptr<AnnotatorLib::Annotation> annotation);
  QJsonObject frameToJson(const shared_ptr<AnnotatorLib::Frame> frame);
  QJsonObject objectToJson(const shared_ptr<AnnotatorLib::Object> object);
  QJsonObject classToJson(const shared_ptr<AnnotatorLib::Class> c);

  QJsonObject session;
  void save();
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of JSONSaver class header
 ************************************************************/

#endif
