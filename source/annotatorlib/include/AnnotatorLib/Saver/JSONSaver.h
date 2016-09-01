// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

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
  void saveAnnotation(Annotation annotation);
  void setPath(std::string path);
  StorageType getType();
  void saveSession(AnnotatorLib::Session* session);
  bool close();

 protected:
  std::string path;
  QJsonObject sessionToJson(AnnotatorLib::Session* session);
  QJsonObject attributeToJson(AnnotatorLib::Attribute* attribute);
  QJsonObject annotationToJson(AnnotatorLib::Annotation* annotation);
  QJsonObject frameToJson(AnnotatorLib::Frame* frame);
  QJsonObject objectToJson(AnnotatorLib::Object* object);
  QJsonObject classToJson(AnnotatorLib::Class* c);

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
