// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_MONGODBLOADER_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_MONGODBLOADER_H

/************************************************************
 MongoDBLoader class header
 ************************************************************/
#include <AnnotatorLib/Loader/AbstractLoader.h>
#include <AnnotatorLib/Loader/Pkg_Loader.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <Poco/MongoDB/Connection.h>

/************************************************************/
/**
 * @brief The MongoDBLoader class
 * Loads saved data from mysql database
 */
class ANNOTATORLIB_API MongoDBLoader
    : public AnnotatorLib::Loader::AbstractLoader {
 public:
  void setPath(std::string path) override;
  AnnotatorLib::StorageType getType() override;
  void loadSession(AnnotatorLib::Session *session) override;

 protected:
  std::string path;
  std::string dbname;

  void loadAttributes(Poco::MongoDB::Connection &connection,
                      AnnotatorLib::Session *session);
  void loadAnnotations(Poco::MongoDB::Connection &connection,
                       AnnotatorLib::Session *session);
  void loadAnnotationAttributes(
      Poco::MongoDB::Connection &connection,
      std::shared_ptr<AnnotatorLib::Annotation> annotation);
  void loadClasses(Poco::MongoDB::Connection &connection,
                   AnnotatorLib::Session *session);
  void loadObjects(Poco::MongoDB::Connection &connection,
                   AnnotatorLib::Session *session);
  void loadObjectAttributes(Poco::MongoDB::Connection &connection,
                            std::shared_ptr<AnnotatorLib::Object> object);
  void loadFrames(Poco::MongoDB::Connection &connection,
                  AnnotatorLib::Session *session);
};

/************************************************************
 End of MongoDBLoader class header
 ************************************************************/

#endif
