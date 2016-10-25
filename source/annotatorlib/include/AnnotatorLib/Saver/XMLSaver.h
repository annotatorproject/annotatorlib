// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_SAVER_XMLSAVER_H
#define ANNOTATOR_ANNOTATORLIB_SAVER_XMLSAVER_H

/************************************************************
 XMLSaver class header
 ************************************************************/
#include <QDomDocument>
#include <QDomElement>

#include <AnnotatorLib/annotatorlib_api.h>
#include "AnnotatorLib/Saver/Pkg_Saver.h"

#include "AnnotatorLib/Saver/AbstractSaver.h"

namespace AnnotatorLib {

class Frame;

namespace Saver {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API XMLSaver : public AbstractSaver {
  // AbstractSaver interface
 public:
  void saveFrame(const Session *session, const shared_ptr<Frame> frame);
  void saveAnnotation(const Annotation annotation);
  void setPath(std::string path);
  StorageType getType();
  void saveSession(const Session *session);
  bool close();

 protected:
  QDomElement meta(const shared_ptr<Frame> frame);
  QDomElement fromObject(const Session *session,
                         const shared_ptr<Object> object,
                         const shared_ptr<Frame> frame);

  std::string path;

  QDomDocument document;
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
