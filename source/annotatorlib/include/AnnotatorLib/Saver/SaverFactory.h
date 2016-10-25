// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_SAVER_SAVERFACTORY_H
#define ANNOTATOR_ANNOTATORLIB_SAVER_SAVERFACTORY_H

/************************************************************
 SaverFactory class header
 ************************************************************/

#include <AnnotatorLib/Saver/Pkg_Saver.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include <string>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Saver/AbstractSaver.h>

namespace AnnotatorLib {
namespace Saver {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API SaverFactory {
 public:
  /**
   *
   * @return saver
   * @param type
   */
  static AbstractSaver *createSaver(std::string type);

  /**
   *
   * @return saver
   * @param type
   */
  static AbstractSaver *createSaver(AnnotatorLib::StorageType type);
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of SaverFactory class header
 ************************************************************/

#endif
