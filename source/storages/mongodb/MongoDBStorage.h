// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_STORAGE_MONGODBSTORAGE_H
#define ANNOTATOR_ANNOTATORLIB_STORAGE_MONGODBSTORAGE_H

/************************************************************
 MySQLStorage class header
 ************************************************************/
#include <AnnotatorLib/Storage/AbstractStorage.h>
#include <AnnotatorLib/Storage/Pkg_Storage.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <Poco/MongoDB/Connection.h>
#include <Poco/MongoDB/Database.h>

/************************************************************/
/**
 * @brief The MongoDBStorage class
 */
class ANNOTATORLIB_API MongoDBStorage : public AnnotatorLib::Storage::AbstractStorage {
 public:
  virtual ~MongoDBStorage();

  virtual bool open() override;

  bool isOpen() override;

  bool flush() override;

  bool isSaved() override;

  virtual bool close() override;

  /**
   * @brief setPath
   * @param path
   * Path should be like:
   * "host=localhost;user=annotator;password=annotator;db=annotator";
   */
  void setPath(std::string path) override;

  AnnotatorLib::StorageType getType() override;

  /**
   * @brief addAnnotation
   * @param annotation
   * @param add_associated_objects
   * @return
   */
  virtual bool addAnnotation(shared_ptr<AnnotatorLib::Annotation> annotation,
                             bool add_associated_objects = true) override;
  /**
   * @brief removeAnnotation
   * @param id
   * @param unregister
   * @return
   */
  virtual shared_ptr<AnnotatorLib::Annotation> removeAnnotation(
      unsigned long id, bool unregister = true) override;

  /**
   * @brief updateAnnotation
   * Informs session that internals of the Annotation have changed.
   * @param annotation
   */
  virtual void updateAnnotation(shared_ptr<AnnotatorLib::Annotation> annotation) override;

  /**
   * @brief addClass
   *  Add a class to the session and to database if open.
   * @param c
   * @return
   */
  virtual bool addClass(shared_ptr<AnnotatorLib::Class> c) override;
  /**
   * @brief removeClass
   * removes class from database if open
   * @param c
   * @return
   */
  virtual shared_ptr<AnnotatorLib::Class> removeClass(AnnotatorLib::Class* c) override;

  virtual void updateClass(shared_ptr<AnnotatorLib::Class> theClass) override;

  /**
   * @brief addObject
   * @param object
   * @param add_associated_objects
   * @return
   */
  virtual bool addObject(shared_ptr<AnnotatorLib::Object> object,
                         bool add_associated_objects = true) override;
  /**
   * @brief removeObject
   * @param id
   * @param remove_annotations
   * @return
   */
  virtual shared_ptr<AnnotatorLib::Object> removeObject(
      unsigned long id, bool remove_annotations = true) override;

  virtual void updateObject(shared_ptr<AnnotatorLib::Object> object) override;

 protected:
  std::string path;
  Poco::MongoDB::Connection* connection = nullptr;
  std::string dbname;

  bool _open = false;
  bool _save = true;

  void insertOrUpdateAnnotationAttributes(shared_ptr<AnnotatorLib::Annotation> annotation);
  void insertOrUpdateObjectAttributes(shared_ptr<AnnotatorLib::Object> object);
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */


/************************************************************
 End of MongoDBStorage class header
 ************************************************************/

#endif
