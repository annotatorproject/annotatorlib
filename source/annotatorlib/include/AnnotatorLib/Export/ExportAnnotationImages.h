// Copyright 2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_EXPORTANNOTATIONIMAGES_H
#define ANNOTATOR_ANNOTATORLIB_EXPORTANNOTATIONIMAGES_H

/************************************************************
 ExportAnnotationImages class header
 ************************************************************/

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Export/AbstractExport.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

namespace AnnotatorLib {
namespace Export {
/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API ExportAnnotationImages : public AbstractExport {
 public:
  ExportAnnotationImages(std::string path);

  /**
   *
   * @return type
   */
  virtual std::string getType() override;

  virtual std::string getPath() override;

  virtual bool equals(std::shared_ptr<AbstractExport> other) override;

 protected:

  std::string path;

  long position = 0;
  std::vector<boost::filesystem::path> images;
  std::vector<boost::filesystem::path>::const_iterator imgIter;
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
