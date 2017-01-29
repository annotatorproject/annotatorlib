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

namespace AnnotatorLib {
namespace Storage {

/************************************************************/
/**
 * @brief The MongoDBStorage class
 */
class ANNOTATORLIB_API MongoDBStorage : public AbstractStorage {
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

  StorageType getType() override;

  /**
   * @brief addAnnotation
   * @param annotation
   * @param add_associated_objects
   * @return
   */
  virtual bool addAnnotation(shared_ptr<Annotation> annotation,
                             bool add_associated_objects = true) override;
  /**
   * @brief removeAnnotation
   * @param id
   * @param unregister
   * @return
   */
  virtual shared_ptr<Annotation> removeAnnotation(
      unsigned long id, bool unregister = true) override;

  /**
   * @brief updateAnnotation
   * Informs session that internals of the Annotation have changed.
   * @param annotation
   */
  virtual void updateAnnotation(shared_ptr<Annotation> annotation) override;

  /**
   * @brief addClass
   *  Add a class to the session and to database if open.
   * @param c
   * @return
   */
  virtual bool addClass(shared_ptr<Class> c) override;
  /**
   * @brief removeClass
   * removes class from database if open
   * @param c
   * @return
   */
  virtual shared_ptr<Class> removeClass(Class* c) override;

  virtual void updateClass(shared_ptr<Class> theClass) override;

  /**
   * @brief addObject
   * @param object
   * @param add_associated_objects
   * @return
   */
  virtual bool addObject(shared_ptr<Object> object,
                         bool add_associated_objects = true) override;
  /**
   * @brief removeObject
   * @param id
   * @param remove_annotations
   * @return
   */
  virtual shared_ptr<Object> removeObject(
      unsigned long id, bool remove_annotations = true) override;

  virtual void updateObject(shared_ptr<Object> object) override;

 protected:
  std::string path;
  Poco::MongoDB::Connection* connection = nullptr;
  std::string dbname;

  bool _open = false;
  bool _save = true;

  void insertOrUpdateAnnotationAttributes(shared_ptr<Annotation> annotation);
  void insertOrUpdateObjectAttributes(shared_ptr<Object> object);
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of MongoDBStorage class header
 ************************************************************/

#endif
