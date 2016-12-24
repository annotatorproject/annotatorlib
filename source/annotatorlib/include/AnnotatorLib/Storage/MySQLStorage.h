// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_STORAGE_MYSQLSTORAGE_H
#define ANNOTATOR_ANNOTATORLIB_STORAGE_MYSQLSTORAGE_H

/************************************************************
 MySQLStorage class header
 ************************************************************/
#include <AnnotatorLib/Storage/AbstractStorage.h>
#include <AnnotatorLib/Storage/Pkg_Storage.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include <QJsonObject>

#include <Poco/Data/SessionPool.h>

namespace AnnotatorLib {
namespace Storage {

/************************************************************/
/**
 * @brief The MySQLStorage class
 */
class ANNOTATORLIB_API MySQLStorage : public AbstractStorage {
  // AbstractStorage interface
 public:
  ~MySQLStorage();

  bool open();

  bool isOpen();

  bool flush();

  bool isSaved();

  bool close();

  /**
   * @brief setPath
   * @param path
   * Path should be like:
   * "host=localhost;user=annotator;password=annotator;db=annotator";
   */
  void setPath(std::string path);

  StorageType getType();

  /**
   * @brief addAnnotation
   * @param annotation
   * @param add_associated_objects
   * @return
   */
  virtual bool addAnnotation(shared_ptr<Annotation> annotation,
                             bool add_associated_objects = true);
  /**
   * @brief removeAnnotation
   * @param id
   * @param unregister
   * @return
   */
  virtual shared_ptr<Annotation> removeAnnotation(unsigned long id,
                                                  bool unregister = true);

  /**
   * @brief addClass
   *  Add a class to the session and to database if open.
   * @param c
   * @return
   */
  virtual bool addClass(shared_ptr<Class> c);
  /**
   * @brief removeClass
   * removes class from database if open
   * @param c
   * @return
   */
  virtual shared_ptr<Class> removeClass(Class* c);

  /**
   * @brief addObject
   * @param object
   * @param add_associated_objects
   * @return
   */
  virtual bool addObject(shared_ptr<Object> object,
                         bool add_associated_objects = true);
  /**
   * @brief removeObject
   * @param id
   * @param remove_annotations
   * @return
   */
  virtual shared_ptr<Object> removeObject(unsigned long id,
                                          bool remove_annotations = true);

 protected:
  std::string path;
  Poco::Data::SessionPool* pool = nullptr;

  bool _open = false;
  bool _save = true;

  /**
   * @brief createTables
   * creates tables in mysql database if they not exist
   */
  void createTables();
  Poco::Data::Statement getStatement();
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of MySQLStorage class header
 ************************************************************/

#endif
