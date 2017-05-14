// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_SAVER_JSONSAVER_H
#define ANNOTATOR_ANNOTATORLIB_SAVER_JSONSAVER_H

/************************************************************
 JSONSaver class header
 ************************************************************/
#include <AnnotatorLib/Class.h>
#include <AnnotatorLib/Storage/AbstractSaver.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <Poco/JSON/Object.h>

namespace AnnotatorLib {
namespace Storage {

/************************************************************/
/**
 * @brief The JSONSaver class
 * writes session to json file.
 */
class ANNOTATORLIB_API JSONSaver : public AbstractSaver {
  // AbstractSaver interface
 public:
  void saveAnnotation(const Annotation annotation) override;
  void setPath(std::string path) override;
  StorageType getType() override;
  void saveSession(const AnnotatorLib::Session* session) override;
  void saveProject(std::shared_ptr<AnnotatorLib::Project> project) override;
  bool close() override;

 protected:
  std::string path;
  Poco::JSON::Object::Ptr sessionToJson(const AnnotatorLib::Session* session);

  Poco::JSON::Object::Ptr attributeToJson(
      const shared_ptr<AnnotatorLib::Attribute> attribute);

  Poco::JSON::Object::Ptr annotationToJson(
      const shared_ptr<AnnotatorLib::Annotation> annotation);

  Poco::JSON::Object::Ptr frameToJson(
      const shared_ptr<AnnotatorLib::Frame> frame);

  Poco::JSON::Object::Ptr objectToJson(
      const shared_ptr<AnnotatorLib::Object> object);

  Poco::JSON::Object::Ptr classToJson(const shared_ptr<AnnotatorLib::Class> c);

  Poco::JSON::Object::Ptr session;
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
