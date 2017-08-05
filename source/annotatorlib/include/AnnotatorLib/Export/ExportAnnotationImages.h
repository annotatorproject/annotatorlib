// Copyright 2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_EXPORTANNOTATIONIMAGES_H
#define ANNOTATOR_ANNOTATORLIB_EXPORTANNOTATIONIMAGES_H

/************************************************************
 ExportAnnotationImages class header
 ************************************************************/

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Export/AbstractExport.h>
#include <AnnotatorLib/Project.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

namespace AnnotatorLib {

class Class;
class Object;

namespace Export {
/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API ExportAnnotationImages : public AbstractExport {
 public:
  ExportAnnotationImages(std::shared_ptr<Project> project, std::string path);

  /**
   *
   * @return type
   */
  virtual std::string getType() override;

  virtual std::string getPath() override;

  virtual void doExport() override;

  virtual bool equals(std::shared_ptr<AbstractExport> other) override;

 protected:
  void exportClass(std::shared_ptr<Class> theClass);
  void exportObject(std::shared_ptr<Object> object);

  std::shared_ptr<Project> project;
  std::string path;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */
}  // of namespace Export
}  // of namespace AnnotatorLib

/************************************************************
 End of ExportAnnotationImages class header
 ************************************************************/

#endif
