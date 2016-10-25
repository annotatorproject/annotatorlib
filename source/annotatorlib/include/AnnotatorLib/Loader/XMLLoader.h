// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_XMLLOADER_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_XMLLOADER_H

/************************************************************
 XMLLoader class header
 ************************************************************/
#include <boost/filesystem.hpp>
#include <vector>

#include <AnnotatorLib/annotatorlib_api.h>
#include "AnnotatorLib/Loader/Pkg_Loader.h"

#include "AnnotatorLib/Loader/AbstractLoader.h"

namespace AnnotatorLib {
namespace Loader {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API XMLLoader : public AbstractLoader {
  // AbstractLoader interface
 public:
  virtual void setPath(std::string path);
  virtual StorageType getType();
  void loadSession(AnnotatorLib::Session *session);

  void findXMLFiles();
  static void loadFile(std::string fileName, AnnotatorLib::Session *session);
  static void loadAnnotation(unsigned long id, unsigned long start,
                             unsigned long end, std::string name, int ulX,
                             int ulY, int lrX, int lrY,
                             AnnotatorLib::Session *session);

  static void parseXY(std::string str, std::string remove, int &x, int &y);

 protected:
  std::string path;
  std::vector<boost::filesystem::path> xmlFiles;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of XMLLoader class header
 ************************************************************/

#endif
