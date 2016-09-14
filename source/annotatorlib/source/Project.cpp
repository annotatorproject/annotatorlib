// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

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

Project::~Project() { delete session; }

Session *Project::getSession() const { return session; }

Storage::AbstractStorage *Project::getStorage() const {
  return (AnnotatorLib::Storage::AbstractStorage *)session;
}

std::string Project::getName() const { return name; }

unsigned long Project::getDuration()
{
  int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now() - time_point_start).count();
  total_duration_sec += elapsed_seconds;
  this->time_point_start = std::chrono::system_clock::now(); //reset
  return this->total_duration_sec;
}

ImageSet *Project::getImageSet() const { return imageSet; }

Project *Project::load(std::string path) {
  Project *project = new Project();
  project->path = path;
  project->load();

  return project;
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

void Project::loadSession() {
  AnnotatorLib::Storage::AbstractStorage *storage =
      AnnotatorLib::Storage::StorageFactory::createStorage(this->storageType);
  storage->setPath(this->storagePath);
  storage->open();
  this->session = (Session *)storage;
  this->time_point_start = std::chrono::system_clock::now();
}

void Project::save(Project *project, std::string path) {
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

  return root;
}

void Project::saveSession() {
  AnnotatorLib::Storage::AbstractStorage *storage =
      (AnnotatorLib::Storage::AbstractStorage *)session;
  storage->flush();
}

QDomElement Project::saveProjectStatistics(QDomDocument &doc)
{
  QDomElement element = doc.createElement("Statistics");
  element.setAttribute(
      "duration", QString::number(getDuration()));
  return element;
}

Project *Project::create(std::string name, ImageSetType imageSetType,
                         std::string imageSetPath, StorageType storageType,
                         std::string storagePath) {
  if (name == "") throw std::runtime_error("Project name is empty");
  if (imageSetType == ImageSetType::UNKNOWN)
    throw std::runtime_error("ImageSetType is unknown");
  if (storageType == StorageType::UNKNOWN)
    throw std::runtime_error("StorageType is unknown");
  return new Project(name, imageSetType, imageSetPath, storageType,
                     storagePath);
}

Project *Project::create(std::string name, std::string imageSetType,
                         std::string imageSetPath, std::string storageType,
                         std::string storagePath) {
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

std::string Project::getImageSetPath() const { return this->imageSet->getPath(); }

void Project::setPath(std::string path) { this->path = path; }

std::string Project::getPath() const { return path; }

}  // of namespace AnnotatorLib

/************************************************************
 End of Project class body
 ************************************************************/
