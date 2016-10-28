// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Project_BODY

/************************************************************
 Project class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Project.h"
#include <AnnotatorLib/Storage/StorageFactory.h>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "AnnotatorLib/ImageSetFactory.h"
#include "AnnotatorLib/Loader/LoaderFactory.h"
#include "AnnotatorLib/Saver/SaverFactory.h"

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
  QFile file(QString::fromStdString(this->path));

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qDebug() << "File could not been opened: "
             << QString::fromStdString(this->path);
    throw std::runtime_error("File could not been opened!");
  }

  QDomDocument doc("Annotator");
  QDomElement root = saveRoot(doc);

  doc.appendChild(root);

  QTextStream ts(&file);
  ts << doc.toString();

  file.close();

  this->session = std::make_shared<Session>();
}

/**
 *
 */
void Project::load() {
  QFile file(QString::fromStdString(this->path));

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "File could not been opened: "
             << QString::fromStdString(this->path);
    throw std::runtime_error("File could not been opened!");
  }

  QDomDocument doc;
  if (!doc.setContent(&file)) {
    file.close();
    throw std::runtime_error("File is not valide!");
  }
  file.close();

  QDomElement root;

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

void Project::loadImageSet(QDomElement &root, ImageSetType &type,
                           std::string &imageSetPath) {
  QDomElement element = root.firstChildElement("ImageSet");
  type = AnnotatorLib::ImageSetTypeFromString(
      element.attribute("type").toStdString());
  imageSetPath = element.attribute("path").toStdString();
}

void Project::loadStorage(QDomElement &root, StorageType &type,
                          std::string &storagePath) {
  QDomElement element = root.firstChildElement("Storage");
  type = AnnotatorLib::StorageTypeFromString(
      element.attribute("type").toStdString());
  storagePath = element.attribute("path").toStdString();
}

void Project::loadProjectStatistics(QDomElement &root) {
  QDomElement element = root.firstChildElement("Statistics");
  if (!element.isNull())
    this->total_duration_sec = element.attribute("duration").toULong();
}

void Project::loadRoot(QDomDocument &doc, QDomElement &root,
                       std::string &name) {
  root = doc.documentElement();
  name = root.tagName().toStdString();
}

void Project::loadProjectSettings(QDomElement &root) {
  QDomElement element = root.firstChildElement("Settings");
  if (!element.isNull())
    this->active = element.attribute("active").toStdString() == "1";
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
  QFile file(QString::fromStdString(this->path));

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qDebug() << "File could not been opened: "
             << QString::fromStdString(this->path);
    throw std::runtime_error("File could not been opened!");
  }

  QDomDocument doc("Annotator");
  QDomElement root = saveRoot(doc);

  doc.appendChild(root);

  QTextStream ts(&file);
  ts << doc.toString();

  file.close();

  saveSession();
}

QDomElement Project::saveImageSet(QDomDocument &doc) {
  if (this->imageSet == nullptr)
    throw std::runtime_error("ImageSet not set properly!");
  QDomElement element = doc.createElement("ImageSet");
  element.setAttribute(
      "type", QString::fromStdString(
                  AnnotatorLib::ImageSetTypeToString(this->imageSetType)));
  element.setAttribute("path",
                       QString::fromStdString(this->imageSet->getPath()));

  return element;
}

QDomElement Project::saveStorage(QDomDocument &doc) {
  if (this->storageType == StorageType::UNKNOWN)
    throw std::runtime_error("StorageType not set properly!");
  QDomElement element = doc.createElement("Storage");
  element.setAttribute(
      "type", QString::fromStdString(
                  AnnotatorLib::StorageTypeToString(this->storageType)));
  element.setAttribute("path", QString::fromStdString(this->storagePath));
  return element;
}

QDomElement Project::saveRoot(QDomDocument &doc) {
  QDomElement root = doc.createElement(QString::fromStdString(this->name));
  root.appendChild(saveStorage(doc));
  root.appendChild(saveImageSet(doc));
  root.appendChild(saveProjectStatistics(doc));
  root.appendChild(saveProjectSettings(doc));

  return root;
}

void Project::saveSession() {
  shared_ptr<AnnotatorLib::Storage::AbstractStorage> storage =
      std::static_pointer_cast<AnnotatorLib::Storage::AbstractStorage>(session);
  storage->flush();
}

QDomElement Project::saveProjectStatistics(QDomDocument &doc) {
  QDomElement element = doc.createElement("Statistics");
  element.setAttribute("duration", QString::number(getDuration()));
  return element;
}

QDomElement Project::saveProjectSettings(QDomDocument &doc) {
  QDomElement element = doc.createElement("Settings");
  element.setAttribute("active", QString(active ? "1" : "0"));
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
