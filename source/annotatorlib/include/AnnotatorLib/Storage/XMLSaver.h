// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_SAVER_XMLSAVER_H
#define ANNOTATOR_ANNOTATORLIB_SAVER_XMLSAVER_H

/************************************************************
 XMLSaver class header
 ************************************************************/
#include <AnnotatorLib/Storage/AbstractSaver.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <Poco/AutoPtr.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>

namespace AnnotatorLib {

class Frame;

namespace Storage {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API XMLSaver : public AbstractSaver {
 public:
  void saveFrame(const Session *session, const shared_ptr<Frame> frame);
  void saveAnnotation(const Annotation annotation) override;
  void setPath(std::string path) override;
  StorageType getType() override;
  void saveSession(const Session *session) override;
  void saveProject(std::shared_ptr<AnnotatorLib::Project> project) override;
  bool close() override;

 protected:
  Poco::AutoPtr<Poco::XML::Element> meta(const shared_ptr<Frame> frame);
  Poco::AutoPtr<Poco::XML::Element> fromObject(const Session *session,
                                               const shared_ptr<Object> object,
                                               const shared_ptr<Frame> frame);

  std::string path;

  Poco::AutoPtr<Poco::XML::Document> document;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of XMLSaver class header
 ************************************************************/

#endif
