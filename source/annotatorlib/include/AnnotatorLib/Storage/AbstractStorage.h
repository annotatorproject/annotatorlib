#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_ABSTRACTSTORAGE_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_ABSTRACTSTORAGE_H

/************************************************************
 AbstractStorage class header
 ************************************************************/

#include <AnnotatorLib/Storage/Pkg_Storage.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Session.h>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>

namespace AnnotatorLib {

class Session;

namespace Storage {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API AbstractStorage : public Session {
 public:
  virtual bool open() = 0;

  virtual bool isOpen() = 0;

  virtual bool flush() = 0;

  virtual bool isSaved() = 0;

  virtual bool close() = 0;

  /**
   *
   * @param path
   */
  virtual void setPath(std::string /*in*/ path) = 0;

  /**
   *
   * @return type
   */
  virtual AnnotatorLib::StorageType getType() = 0;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of AbstractStorage class header
 ************************************************************/

#endif
