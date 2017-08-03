// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Project_BODY

/************************************************************
 Project class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/ImageSet/ImageSetFactory.h>
#include <AnnotatorLib/Project.h>
#include <AnnotatorLib/Storage/StorageFactory.h>

#include <fstream>

#include <Poco/AutoPtr.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/Text.h>
#include <Poco/SAX/InputSource.h>
#include <Poco/Util/XMLConfiguration.h>
#include <Poco/XML/XMLWriter.h>

// Derived includes directives

namespace AnnotatorLib {

// static attributes (if any)

Project::Project() {}

Project::Project(std::string name, std::string imageSetType,
                 std::string imageSetPath, std::string storageType,
                 std::string storagePath) {
  this->name = name;
  this->imageSetType = imageSetType;
  this->storageType = storageType;
  this->storagePath = storagePath;
  this->imageSet =
      AnnotatorLib::ImageSet::ImageSetFactory::instance()->createImageSet(
          imageSetType, imageSetPath);
}

Project::~Project() {}

std::shared_ptr<AnnotatorLib::Session> Project::getSession() const {
  return session;
}

std::shared_ptr<Storage::AbstractStorage> Project::getStorage() const {
  return std::static_pointer_cast<AnnotatorLib::Storage::AbstractStorage>(
      session);
}

std::string Project::getName() const { return name; }

unsigned long Project::updateDuration() {
  int elapsed_seconds =
      active
          ? std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now() - time_point_start)
                .count()
          : 0;
  total_duration_sec += elapsed_seconds;
  this->time_point_start = std::chrono::system_clock::now();  // reset
  return total_duration_sec;
}

unsigned long Project::getDuration() { return updateDuration(); }

std::shared_ptr<ImageSet::AbstractImageSet> Project::getImageSet() const {
  return imageSet;
}

std::shared_ptr<AnnotatorLib::Project> Project::load(std::string path) {
  std::shared_ptr<AnnotatorLib::Project> project =
      std::shared_ptr<AnnotatorLib::Project>(new Project());
  project->path = path;
  project->load();

  return project;
}

/**
 *
 */
void Project::create() {
  saveConfig();
  this->session = std::make_shared<Session>();
}

/**
 *
 */
void Project::load() {
  std::fstream istr;
  istr.open(path, std::ios::in);
  Poco::AutoPtr<Poco::Util::XMLConfiguration> config =
      new Poco::Util::XMLConfiguration(istr);

  this->name = config->getString("Name");

  this->imageSetType = config->getString("ImageSet[@type]");
  std::string imageSetPath = config->getString("ImageSet[@path]");

  this->storageType = config->getString("Storage[@type]");
  this->storagePath = config->getString("Storage[@path]");

  this->total_duration_sec = config->getUInt64("Statistics[@duration]");
  this->active = config->getBool("Settings[@active]");

  this->imageSet =
      AnnotatorLib::ImageSet::ImageSetFactory::instance()->createImageSet(
          this->imageSetType, imageSetPath);

  istr.close();
  loadSession();
}

void Project::loadSession() {
  shared_ptr<AnnotatorLib::Storage::AbstractStorage> storage =
      AnnotatorLib::Storage::StorageFactory::instance()->createStorage(
          this->storageType);
  if (storage == nullptr)
    throw std::runtime_error("Storage " + this->storageType +
                             " is not available.");
  storage->setPath(this->storagePath);
  storage->open();
  this->session = std::static_pointer_cast<AnnotatorLib::Session>(storage);
  this->time_point_start = std::chrono::system_clock::now();
}

void Project::saveConfig() {
  std::fstream ostr;
  ostr.open(path, std::ios::out);

  Poco::XML::DOMWriter writer;
  writer.setNewLine("\n");
  writer.setOptions(Poco::XML::XMLWriter::PRETTY_PRINT);

  Poco::AutoPtr<Poco::Util::XMLConfiguration> config =
      new Poco::Util::XMLConfiguration();

  config->setString("Name", this->name);
  config->setString("ImageSet[@type]", this->imageSetType);
  config->setString("ImageSet[@path]", imageSet->getPath());
  config->setString("Storage[@type]", this->storageType);
  config->setString("Storage[@path]", this->storagePath);
  config->setUInt64("Statistics[@duration]", this->total_duration_sec);
  config->setBool("Settings[@active]", this->active);

  config->save(writer, ostr);
  ostr.close();
}

void Project::save(std::shared_ptr<AnnotatorLib::Project> project,
                   std::string path) {
  project->path = path;
  project->save();
}

void Project::save() {
  saveConfig();
  saveSession();
}

void Project::saveSession() {
  shared_ptr<AnnotatorLib::Storage::AbstractStorage> storage =
      std::static_pointer_cast<AnnotatorLib::Storage::AbstractStorage>(session);
  storage->flush();
}

std::shared_ptr<AnnotatorLib::Project> Project::create(
    std::string name, std::string imageSetType, std::string imageSetPath,
    std::string storageType, std::string storagePath) {
  if (name == "") throw std::runtime_error("Project name is empty");
  if (imageSetType == "unknown")
    throw std::runtime_error("ImageSetType is unknown");
  if (storageType == "unknown")
    throw std::runtime_error("StorageType is unknown");
  return std::shared_ptr<AnnotatorLib::Project>(
      new Project(name, imageSetType, imageSetPath, storageType, storagePath));
}

bool Project::equals(Project *other) const {
  if (this == other) return true;
  if (this->name != other->name) return false;
  if (this->path != other->path) return false;
  if (this->storageType != other->storageType) return false;
  if (this->storagePath != other->storagePath) return false;
  if (this->imageSetType != other->imageSetType) return false;
  if (!this->imageSet->equals(other->imageSet)) return false;
  return true;
}

bool Project::equals(shared_ptr<Project> other) const {
  return this->equals(other.get());
}

std::string Project::getImageSetPath() const {
  return this->imageSet->getPath();
}

void Project::setPath(std::string path) { this->path = path; }

std::string Project::getPath() const { return path; }

void Project::setActive(bool b) {
  updateDuration();
  active = b;
}

bool Project::isActive() const { return active; }

}  // of namespace AnnotatorLib

/************************************************************
 End of Project class body
 ************************************************************/
