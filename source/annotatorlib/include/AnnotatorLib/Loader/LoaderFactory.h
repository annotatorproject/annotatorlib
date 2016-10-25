// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_LOADERFACTORY_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_LOADERFACTORY_H

/************************************************************
 LoaderFactory class header
 ************************************************************/
#include <string>

#include <AnnotatorLib/Loader/Pkg_Loader.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Loader/AbstractLoader.h>

namespace AnnotatorLib {
namespace Loader {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API LoaderFactory {
 public:
  /**
   *
   * @return loader
   * @param type
   */
  static AbstractLoader *createLoader(std::string /*in*/ type);

  /**
   *
   * @param type
   * @return loader
   */
  static AbstractLoader *createLoader(AnnotatorLib::StorageType type);
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of LoaderFactory class header
 ************************************************************/

#endif
