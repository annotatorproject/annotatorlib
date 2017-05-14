// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_MYSQLLOADER_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_MYSQLLOADER_H

/************************************************************
 MySQLLoader class header
 ************************************************************/
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Storage/AbstractLoader.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <Poco/Data/Session.h>

namespace AnnotatorLib {
namespace Storage {

/************************************************************/
/**
 * @brief The MySQLLoader class
 * Loads saved data from mysql database
 */
class ANNOTATORLIB_API MySQLLoader : public AbstractLoader {
  // AbstractLoader interface
 public:
  void setPath(std::string path);
  StorageType getType();
  void loadSession(AnnotatorLib::Session *session);

 protected:
  std::string path;

  void loadAttributes(Poco::Data::Session &sqlSession,
                      AnnotatorLib::Session *session);
  void loadAnnotations(Poco::Data::Session &sqlSession,
                       AnnotatorLib::Session *session);
  void loadAnnotationAttributes(
      Poco::Data::Session &sqlSession,
      std::shared_ptr<AnnotatorLib::Annotation> annotation);
  void loadClasses(Poco::Data::Session &sqlSession,
                   AnnotatorLib::Session *session);
  void loadObjects(Poco::Data::Session &sqlSession,
                   AnnotatorLib::Session *session);
  void loadObjectAttributes(Poco::Data::Session &sqlSession,
                            std::shared_ptr<AnnotatorLib::Object> object);
  void loadFrames(Poco::Data::Session &sqlSession,
                  AnnotatorLib::Session *session);
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of MySQLLoader class header
 ************************************************************/

#endif
