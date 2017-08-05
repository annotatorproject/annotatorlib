// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_EXPORTFACTORY_H
#define ANNOTATOR_ANNOTATORLIB_EXPORTFACTORY_H

/************************************************************
 ImageSetFactory class header
 ************************************************************/

#include <list>
#include <map>
#include <memory>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Export/AbstractExport.h>
#include <AnnotatorLib/Export/ExportPlugin.h>
#include <AnnotatorLib/Project.h>
#include <AnnotatorLib/annotatorlib_api.h>

namespace AnnotatorLib {
namespace Export {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API ExportFactory {
 public:
  /**
   *
   * @param type
   * @return imageSet
   */
  std::shared_ptr<AbstractExport> createExport(std::string type,
                                               std::shared_ptr<Project> project,
                                               std::string path);

  std::list<std::string> availableExports();

  /**
   * @brief loadPlugins
   * @param dir the path to plugins
   */
  void loadPlugins(std::string dir);

  /**
   * @brief instance
   * @return singleton for StorageFactory
   */
  static ExportFactory* instance();

  ~ExportFactory();

 protected:
  void addAvailableExport(ExportPlugin* plugin);

 private:
  ExportFactory() {}
  std::list<std::string> _availableExports{"annotationimages"};
  std::map<std::string, std::shared_ptr<ExportPlugin>> plugins;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Export
}  // of namespace AnnotatorLib

/************************************************************
 End of ImageSetFactory class header
 ************************************************************/

#endif
