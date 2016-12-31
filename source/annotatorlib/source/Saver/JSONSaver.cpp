// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Saver_JSONSaver_BODY

/************************************************************
 JSONSaver class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Saver/JSONSaver.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <memory>
#include <unordered_map>
#include "AnnotatorLib/Annotation.h"
#include "AnnotatorLib/Attribute.h"
#include "AnnotatorLib/Frame.h"
#include "AnnotatorLib/Object.h"
#include "AnnotatorLib/Session.h"

using std::unique_ptr;
using std::pair;
using std::unordered_map;

namespace AnnotatorLib {
namespace Saver {

void JSONSaver::saveAnnotation(const Annotation annotation) {}

void JSONSaver::setPath(std::string path) { this->path = path; }

StorageType JSONSaver::getType() { return AnnotatorLib::StorageType::JSON; }

void JSONSaver::saveSession(const Session* session) {
  this->session = sessionToJson(session);
}

bool JSONSaver::close() {
  save();
  return true;
}

QJsonObject JSONSaver::sessionToJson(const Session* session) {
  QJsonObject json;

  // insert list of objects
  QJsonArray objects;
  for (auto& pair : session->getObjects()) {
    if (pair.second->hasAnnotations())
      objects.append(objectToJson(pair.second));
  }
  json["objects"] = objects;

  // insert list of attributes
  QJsonArray attributes;
  for (auto& pair : session->getAttributes()) {
    attributes.append(attributeToJson(pair.second));
  }
  json["attributes"] = attributes;

  // insert list of annotations
  QJsonArray annotations;
  for (auto& pair : session->getAnnotations()) {
    annotations.append(annotationToJson(pair.second));
  }
  json["annotations"] = annotations;

  // insert list of classes
  QJsonArray classes;
  for (auto& pair : session->getClasses()) {
    classes.append(classToJson(pair.second));
  }
  json["classes"] = classes;

  // insert list of frames
  QJsonArray frames;
  for (auto& pair : session->getFrames()) {
    if (pair.second->hasAnnotations()) frames.append(frameToJson(pair.second));
  }
  json["frames"] = frames;

  return json;
}

QJsonObject JSONSaver::attributeToJson(
    const shared_ptr<AnnotatorLib::Attribute> attribute) {
  QJsonObject json;
  json["id"] = QString::number(attribute->getId());
  json["name"] = QString::fromStdString(attribute->getName());
  json["type"] = QString::fromStdString(
      AnnotatorLib::AttributeTypeToString(attribute->getType()));
  json["default"] = QString::fromStdString(attribute->getValue()->toString());
  return json;
}

QJsonObject JSONSaver::annotationToJson(
    const shared_ptr<AnnotatorLib::Annotation> annotation) {
  QJsonObject json;
  json["id"] = QString::number(annotation->getId());
  json["object"] = QString::number(annotation->getObject()->getId());
  json["frame"] = QString::number(annotation->getFrame()->getFrameNumber());

  json["x"] = QString::number(annotation->getX());
  json["y"] = QString::number(annotation->getY());
  json["width"] = QString::number(annotation->getWidth());
  json["height"] = QString::number(annotation->getHeight());
  json["type"] = QString::fromStdString(
      AnnotatorLib::AnnotationTypeToString(annotation->getType()));

  if (annotation->getPrevious() != nullptr) {
    json["previous"] = QString::number(annotation->getPrevious()->getId());
  }

  if (annotation->getNext() != nullptr) {
    json["next"] = QString::number(annotation->getNext()->getId());
  }

  // insert list of attributes
  QJsonArray attributes;
  for (shared_ptr<Attribute> attribute : annotation->getAttributes()) {
    attributes.append(QString::number(attribute->getId()));
  }
  json["attributes"] = attributes;

  return json;
}

QJsonObject JSONSaver::frameToJson(
    const shared_ptr<AnnotatorLib::Frame> frame) {
  QJsonObject json;

  json["number"] = QString::number(frame->getFrameNumber());

  // insert list of attributes
  QJsonArray attributes;
  for (auto& pair : frame->getAttributes()) {
    attributes.append(QString::number(pair.second->getId()));
  }
  json["attributes"] = attributes;

  // insert list of annotations
  QJsonArray annotations;
  for (std::pair<unsigned long, weak_ptr<Annotation>> pair :
       frame->getAnnotations()) {
    annotations.append(QString::number(pair.second.lock()->getId()));
  }
  json["annotations"] = annotations;

  return json;
}

QJsonObject JSONSaver::objectToJson(const shared_ptr<Object> object) {
  QJsonObject json;
  json["id"] = QString::number(object->getId());
  json["name"] = QString::fromStdString(object->getName());
  if (object->getClass())
    json["class"] = QString::number(object->getClass()->getId());
  else
    json["class"] = QString("no_class");

  // insert list of attributes
  QJsonArray attributes;
  for (shared_ptr<Attribute>& attribute : object->getAttributes()) {
    attributes.append(QString::number(attribute->getId()));
  }
  json["attributes"] = attributes;

  // insert list of annotations
  QJsonArray annotations;
  for (auto& pair : object->getAnnotations()) {
    annotations.append(QString::number(pair.second.lock()->getId()));
  }
  json["annotations"] = annotations;

  // insert list of frames
  QJsonArray frames;
  for (auto frame : object->getFrames()) {
    frames.append(QString::number(frame->getFrameNumber()));
  }
  json["frames"] = frames;

  return json;
}

QJsonObject JSONSaver::classToJson(const shared_ptr<AnnotatorLib::Class> c) {
  QJsonObject json;
  json["id"] = QString::number(c->getId());
  json["name"] = QString::fromStdString(c->getName());
  return json;
}

void JSONSaver::save() {
  QFile file(QString::fromStdString(this->path));
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QJsonDocument document;
    // QJsonObject object;
    // object["session"] = this->session;
    document.setObject(this->session);
    file.write(document.toJson());
  }
  file.close();
}

// static attributes (if any)

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of JSONSaver class body
 ************************************************************/
