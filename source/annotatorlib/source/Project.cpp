// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Project_BODY

/************************************************************
 Project class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/Project.h>
#include <AnnotatorLib/Storage/StorageFactory.h>
#include <AnnotatorLib/ImageSetFactory.h>
#include <AnnotatorLib/Loader/LoaderFactory.h>
#include <AnnotatorLib/Saver/SaverFactory.h>

#include <fstream>

#include <Poco/AutoPtr.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Element.h>
#include <Poco/XML/XMLWriter.h>
#include <Poco/DOM/Text.h>
#include <Poco/SAX/InputSource.h>
#include <Poco/DOM/DOMParser.h>

// Derived includes directives

namespace AnnotatorLib {

// static attributes (if any)

Project::Project() {}

Project::Project(std::string name, ImageSetType imageSetType,
                 std::string imageSetPath, StorageType storageType,
                 std::string storagePath) {
  this->name = name;
  this->imageSetType = imageSetType;
  this->storageType = storageType;
  this->storagePath = storagePath;
  this->imageSet =
      AnnotatorLib::ImageSetFactory::createImageSet(imageSetType, imageSetPath);
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

ImageSet *Project::getImageSet() const { return imageSet; }

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

    std::ofstream ostr(path, std::ios::out);
    Poco::XML::DOMWriter writer;
    writer.setNewLine("\n");
    writer.setOptions(Poco::XML::XMLWriter::PRETTY_PRINT);
    Poco::AutoPtr<Poco::XML::Document> document = new Poco::XML::Document;
    Poco::AutoPtr<Poco::XML::Element> root = saveRoot(document);
    document->appendChild(root);

  this->session = std::make_shared<Session>();
}

/**
 *
 */
void Project::load() {

    std::ifstream in(path);
    Poco::XML::InputSource src(in);

    Poco::XML::DOMParser parser;
    Poco::AutoPtr<Poco::XML::Document> doc = parser.parse(&src);

    Poco::AutoPtr<Poco::XML::Element> root;

  loadRoot(doc, root, this->name);
  std::string imageSetPath;
  loadImageSet(root, this->imageSetType, imageSetPath);
  this->imageSet = AnnotatorLib::ImageSetFactory::createImageSet(
      this->imageSetType, imageSetPath);

  loadStorage(root, this->storageType, this->storagePath);
  loadProjectStatistics(root);
  loadProjectSettings(root);
  loadSession();
}

void Project::loadImageSet(Poco::AutoPtr<Poco::XML::Element> root, ImageSetType &type,
                           std::string &imageSetPath) {
  Poco::AutoPtr<Poco::XML::Element> element = root->getChildElement("ImageSet");
  type = AnnotatorLib::ImageSetTypeFromString(
      element->getAttribute("type"));
  imageSetPath = element->getAttribute("path");
}

void Project::loadStorage(Poco::AutoPtr<Poco::XML::Element> root, StorageType &type,
                          std::string &storagePath) {
  Poco::AutoPtr<Poco::XML::Element> element = root->getChildElement("Storage");
  type = AnnotatorLib::StorageTypeFromString(
      element->getAttribute("type"));
  storagePath = element->getAttribute("path");
}

void Project::loadProjectStatistics(Poco::AutoPtr<Poco::XML::Element> root) {
  Poco::AutoPtr<Poco::XML::Element> element = root->getChildElement("Statistics");
  if (element)
    this->total_duration_sec = std::stoul(element->getAttribute("duration"));
}

void Project::loadRoot(Poco::AutoPtr<Poco::XML::Document> doc, Poco::AutoPtr<Poco::XML::Element> root,
                       std::string &name) {
  root = doc->documentElement();
  name = root->tagName();
}

void Project::loadProjectSettings(Poco::AutoPtr<Poco::XML::Element> root) {
  Poco::AutoPtr<Poco::XML::Element> element = root->getChildElement("Settings");
  if (element)
    this->active = element->getAttribute("active") == "1";
}

void Project::loadSession() {
  shared_ptr<AnnotatorLib::Storage::AbstractStorage> storage =
      AnnotatorLib::Storage::StorageFactory::createStorage(this->storageType);
  storage->setPath(this->storagePath);
  storage->open();
  this->session = std::static_pointer_cast<AnnotatorLib::Session>(storage);
  this->time_point_start = std::chrono::system_clock::now();
}

void Project::save(std::shared_ptr<AnnotatorLib::Project> project,
                   std::string path) {
  project->path = path;
  project->save();
}

void Project::save() {

    std::ofstream ostr(path, std::ios::out);
    Poco::XML::DOMWriter writer;
    writer.setNewLine("\n");
    writer.setOptions(Poco::XML::XMLWriter::PRETTY_PRINT);
    Poco::AutoPtr<Poco::XML::Document> document = new Poco::XML::Document;
    Poco::AutoPtr<Poco::XML::Element> root = saveRoot(document);
    document->appendChild(root);

  saveSession();
}

Poco::AutoPtr<Poco::XML::Element> Project::saveImageSet(Poco::AutoPtr<Poco::XML::Document> doc) {
  if (this->imageSet == nullptr)
    throw std::runtime_error("ImageSet not set properly!");
  Poco::AutoPtr<Poco::XML::Element> element = doc->createElement("ImageSet");
  element->setAttribute(
      "type", AnnotatorLib::ImageSetTypeToString(this->imageSetType));
  element->setAttribute("path", this->imageSet->getPath());
  return element;
}

Poco::AutoPtr<Poco::XML::Element> Project::saveStorage(Poco::AutoPtr<Poco::XML::Document> doc) {
  if (this->storageType == StorageType::UNKNOWN)
    throw std::runtime_error("StorageType not set properly!");
  Poco::AutoPtr<Poco::XML::Element> element = doc->createElement("Storage");
  element->setAttribute(
      "type", AnnotatorLib::StorageTypeToString(this->storageType));
  element->setAttribute("path", this->storagePath);
  return element;
}

Poco::AutoPtr<Poco::XML::Element> Project::saveRoot(Poco::AutoPtr<Poco::XML::Document> doc) {
  Poco::AutoPtr<Poco::XML::Element> root = doc->createElement(this->name);
  root->appendChild(saveStorage(doc));
  root->appendChild(saveImageSet(doc));
  root->appendChild(saveProjectStatistics(doc));
  root->appendChild(saveProjectSettings(doc));

  return root;
}

void Project::saveSession() {
  shared_ptr<AnnotatorLib::Storage::AbstractStorage> storage =
      std::static_pointer_cast<AnnotatorLib::Storage::AbstractStorage>(session);
  storage->flush();
}

Poco::AutoPtr<Poco::XML::Element> Project::saveProjectStatistics(Poco::AutoPtr<Poco::XML::Document> doc) {
  Poco::AutoPtr<Poco::XML::Element> element = doc->createElement("Statistics");
  element->setAttribute("duration", std::to_string(getDuration()));
  return element;
}

Poco::AutoPtr<Poco::XML::Element> Project::saveProjectSettings(Poco::AutoPtr<Poco::XML::Document> doc) {
  Poco::AutoPtr<Poco::XML::Element> element = doc->createElement("Settings");
  element->setAttribute("active", active ? "1" : "0");
  return element;
}

std::shared_ptr<AnnotatorLib::Project> Project::create(
    std::string name, ImageSetType imageSetType, std::string imageSetPath,
    StorageType storageType, std::string storagePath) {
  if (name == "") throw std::runtime_error("Project name is empty");
  if (imageSetType == ImageSetType::UNKNOWN)
    throw std::runtime_error("ImageSetType is unknown");
  if (storageType == StorageType::UNKNOWN)
    throw std::runtime_error("StorageType is unknown");
  return std::shared_ptr<AnnotatorLib::Project>(
      new Project(name, imageSetType, imageSetPath, storageType, storagePath));
}

std::shared_ptr<AnnotatorLib::Project> Project::create(
    std::string name, std::string imageSetType, std::string imageSetPath,
    std::string storageType, std::string storagePath) {
  AnnotatorLib::ImageSetType iType =
      AnnotatorLib::ImageSetTypeFromString(imageSetType);
  AnnotatorLib::StorageType sType =
      AnnotatorLib::StorageTypeFromString(storageType);

  return create(name, iType, imageSetPath, sType, storagePath);
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
