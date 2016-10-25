// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_SQLLOADER_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_SQLLOADER_H

/************************************************************
 SQLLoader class header
 ************************************************************/
#include <AnnotatorLib/annotatorlib_api.h>
#include "AnnotatorLib/Loader/Pkg_Loader.h"

#include "AnnotatorLib/Loader/AbstractLoader.h"

namespace AnnotatorLib {
namespace Loader {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API SQLLoader : public AbstractLoader {
  // AbstractLoader interface
 public:
  void setPath(std::string path);
  StorageType getType();
  void loadSession(AnnotatorLib::Session* session);
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of SQLLoader class header
 ************************************************************/

#endif
