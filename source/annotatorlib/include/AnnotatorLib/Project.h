// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_PROJECT_H
#define ANNOTATOR_ANNOTATORLIB_PROJECT_H

/************************************************************
 Project class header
 ************************************************************/
#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include <AnnotatorLib/ImageSet.h>
#include <AnnotatorLib/Session.h>

#include <string>
#include <chrono>
#include <ctime>
#include <memory>

#include <Poco/AutoPtr.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>

namespace AnnotatorLib {

namespace Storage {
class AbstractStorage;
}

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API Project {
 public:
  /**
   * @brief create
   * @param name
   * @param imageSetType
   * @param imageSetPath
   * @param storageType
   * @param storagePath
   * @return
   */
  static std::shared_ptr<AnnotatorLib::Project> create(
      std::string name, ImageSetType imageSetType, std::string imageSetPath,
      StorageType storageType, std::string storagePath);

  /**
   * @brief create
   * @param name
   * @param imageSetType
   * @param imageSetPath
   * @param storageType
   * @param storagePath
   * @return
   */
  static std::shared_ptr<AnnotatorLib::Project> create(std::string name,
                                                       std::string imageSetType,
                                                       std::string imageSetPath,
                                                       std::string storageType,
                                                       std::string storagePath);

  /**
   *
   * @param path
   * @return project
   */
  static std::shared_ptr<AnnotatorLib::Project> load(std::string path);

  ///////////////////////////////////////////////

  ~Project();

  std::shared_ptr<AnnotatorLib::Session> getSession() const;

  std::shared_ptr<Storage::AbstractStorage> getStorage() const;

  std::string getName() const;

  /**
   * @brief Get the total spended time of this project in seconds.
   * @return
   */
  unsigned long getDuration();

  ImageSet *getImageSet() const;

  /**
   * @brief load
   */
  void load();

  /**
   * @brief create
   */
  void create();

  /**
   *
   * @param project
   * @param path
   */
  static void save(std::shared_ptr<AnnotatorLib::Project> project,
                   std::string path);

  /**
   * @brief save
   */
  void save();

  /**
   * @brief equals
   * @param other
   * @return
   */
  bool equals(Project *other) const;
  /**
   * @brief equals
   * @param other
   * @return
   */
  bool equals(shared_ptr<Project> other) const;
  /**
   * @brief getImageSetPath
   * @return
   */
  std::string getImageSetPath() const;
  /**
   * @brief setPath
   * @param path
   */
  void setPath(std::string path);

  /**
   * @brief getPath
   * @return
   */
  std::string getPath() const;

  /**
   * Set a flag that project is active or locked.
   * Enables/Disables the timer also for updating the total labeling duration.
   * @brief setActive
   * @param b
   */
  void setActive(bool b);

  /**
   * @brief isActive
   * @return
   */
  bool isActive() const;

 protected:
  Project();

  Project(std::string name, ImageSetType imageSetType, std::string imageSetPath,
          StorageType storageType, std::string storagePath);

  /**
   * @brief loadSession
   */
  void loadSession();

  void loadImageSet(Poco::AutoPtr<Poco::XML::Element> root, ImageSetType &type,
                    std::string &imageSetPath);

  void loadStorage(Poco::AutoPtr<Poco::XML::Element> root, StorageType &type,
                   std::string &storagePath);

  void loadRoot(Poco::AutoPtr<Poco::XML::Document> doc, Poco::AutoPtr<Poco::XML::Element> root, std::string &name);

  void loadProjectSettings(Poco::AutoPtr<Poco::XML::Element> root);

  void loadProjectStatistics(Poco::AutoPtr<Poco::XML::Element> root);

  /**
   * @brief saveSession
   */
  void saveSession();

  Poco::AutoPtr<Poco::XML::Element> saveImageSet(Poco::AutoPtr<Poco::XML::Document> doc);

  Poco::AutoPtr<Poco::XML::Element> saveStorage(Poco::AutoPtr<Poco::XML::Document> doc);

  Poco::AutoPtr<Poco::XML::Element> saveRoot(Poco::AutoPtr<Poco::XML::Document> doc);

  Poco::AutoPtr<Poco::XML::Element> saveProjectStatistics(Poco::AutoPtr<Poco::XML::Document> doc);

  Poco::AutoPtr<Poco::XML::Element> saveProjectSettings(Poco::AutoPtr<Poco::XML::Document> doc);

  /**
   * Updates the total duration by the elapsed time since last update if project
   * is active.
   * @brief updateDuration
   * @return current duration in seconds
   */
  unsigned long updateDuration();

  ///////////////////////////////////////////////

  std::string name = "";

  std::string path = "";

  unsigned long total_duration_sec = 0;

  ImageSetType imageSetType = ImageSetType::UNKNOWN;

  ImageSet *imageSet = nullptr;

  StorageType storageType = StorageType::UNKNOWN;

  std::string storagePath = "";

  std::shared_ptr<AnnotatorLib::Session> session = nullptr;

  std::chrono::time_point<std::chrono::system_clock> time_point_start;

  bool active = true;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of Project class header
 ************************************************************/

#endif
