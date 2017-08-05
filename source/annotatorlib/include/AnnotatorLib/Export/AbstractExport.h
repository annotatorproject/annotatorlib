// Copyright 2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_EXPORT_H
#define ANNOTATOR_ANNOTATORLIB_EXPORT_H

/************************************************************
 Export class header
 ************************************************************/

#include <memory>
#include <string>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Image.h>
#include <AnnotatorLib/annotatorlib_api.h>

namespace AnnotatorLib {
namespace Export {
/************************************************************/

class ANNOTATORLIB_API AbstractExport {
 public:
  /**
   *
   * @return type
   */
  virtual std::string getType() = 0;

  virtual std::string getPath() = 0;

  virtual bool equals(std::shared_ptr<AbstractExport> other) = 0;

  virtual void doExport() = 0;

  virtual ~AbstractExport() {}
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Export
}  // of namespace AnnotatorLib

/************************************************************
 End of ImageSet class header
 ************************************************************/

#endif
