// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Saver_JSONSaver_BODY

/************************************************************
 JSONSaver class body
 ************************************************************/

// include associated header file

#include "AnnotatorLib/Storage/JSONSaver.h"
#include "AnnotatorLib/Annotation.h"
#include "AnnotatorLib/Attribute.h"
#include "AnnotatorLib/Frame.h"
#include "AnnotatorLib/Object.h"
#include "AnnotatorLib/Session.h"

#include <fstream>
#include <memory>
#include <unordered_map>

#include <Poco/FileStream.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/PrintHandler.h>

using std::unique_ptr;
using std::pair;
using std::unordered_map;

namespace AnnotatorLib {
namespace Storage {

void JSONSaver::saveAnnotation(const Annotation annotation) {}

void JSONSaver::setPath(std::string path) { this->path = path; }

StorageType JSONSaver::getType() { return AnnotatorLib::StorageType::JSON; }

void JSONSaver::saveSession(const Session* session) {
  this->session = sessionToJson(session);
}

void JSONSaver::saveProject(std::shared_ptr<Project> project) {
  saveSession(project->getSession().get());
}

bool JSONSaver::close() {
  save();
  return true;
}

Poco::JSON::Object::Ptr JSONSaver::sessionToJson(const Session* session) {
  Poco::JSON::Object::Ptr json = new Poco::JSON::Object;

  // insert list of objects
  Poco::JSON::Array::Ptr objects = new Poco::JSON::Array;
  for (auto& pair : session->getObjects()) {
    if (pair.second->hasAnnotations()) objects->add(objectToJson(pair.second));
  }
  json->set("objects", objects);

  // insert list of attributes
  Poco::JSON::Array::Ptr attributes = new Poco::JSON::Array;
  for (auto& pair : session->getAttributes()) {
    attributes->add(attributeToJson(pair.second));
  }
  json->set("attributes", attributes);

  // insert list of annotations
  Poco::JSON::Array::Ptr annotations = new Poco::JSON::Array;
  for (auto& pair : session->getAnnotations()) {
    annotations->add(annotationToJson(pair.second));
  }
  json->set("annotations", annotations);

  // insert list of classes
  Poco::JSON::Array::Ptr classes = new Poco::JSON::Array;
  for (auto& pair : session->getClasses()) {
    classes->add(classToJson(pair.second));
  }
  json->set("classes", classes);

  // insert list of frames
  Poco::JSON::Array::Ptr frames = new Poco::JSON::Array;
  for (auto& pair : session->getFrames()) {
    if (pair.second->hasAnnotations() || pair.second->hasAttributes())
      frames->add(frameToJson(pair.second));
  }
  json->set("frames", frames);

  return json;
}

Poco::JSON::Object::Ptr JSONSaver::attributeToJson(
    const shared_ptr<Attribute> attribute) {
  Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
  json->set("id", std::to_string(attribute->getId()));
  json->set("name", attribute->getName());
  json->set("type", AnnotatorLib::AttributeTypeToString(attribute->getType()));
  json->set("value", attribute->getValue()->toString());
  return json;
}

Poco::JSON::Object::Ptr JSONSaver::annotationToJson(
    const shared_ptr<Annotation> annotation) {
  Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
  json->set("id", std::to_string(annotation->getId()));
  json->set("object", std::to_string(annotation->getObject()->getId()));
  json->set("frame", std::to_string(annotation->getFrame()->getFrameNumber()));

  json->set("x", std::to_string(annotation->getX()));
  json->set("y", std::to_string(annotation->getY()));
  json->set("width", std::to_string(annotation->getWidth()));
  json->set("height", std::to_string(annotation->getHeight()));

  json->set("type",
            AnnotatorLib::AnnotationTypeToString(annotation->getType()));
  if (annotation->getPrevious() != nullptr) {
    json->set("previous", std::to_string(annotation->getPrevious()->getId()));
  }
  if (annotation->getNext() != nullptr) {
    json->set("next", std::to_string(annotation->getNext()->getId()));
  }

  Poco::JSON::Array::Ptr attributes = new Poco::JSON::Array;
  for (std::shared_ptr<Attribute> attribute : annotation->getAttributes()) {
    attributes->add(attributeToJson(attribute));
  }
  json->set("attributes", attributes);

  return json;
}

Poco::JSON::Object::Ptr JSONSaver::frameToJson(const shared_ptr<Frame> frame) {
  Poco::JSON::Object::Ptr json = new Poco::JSON::Object;

  json->set("number", std::to_string(frame->getFrameNumber()));

  Poco::JSON::Array::Ptr attributes = new Poco::JSON::Array;
  for (std::shared_ptr<Attribute> attribute : frame->getAttributes()) {
    attributes->add(attributeToJson(attribute));
  }
  json->set("attributes", attributes);

  Poco::JSON::Array::Ptr annotations = new Poco::JSON::Array;

  for (std::pair<unsigned long, weak_ptr<Annotation>> pair :
       frame->getAnnotations()) {
    annotations->add(std::to_string(pair.second.lock()->getId()));
  }
  json->set("annotations", annotations);
  return json;
}

Poco::JSON::Object::Ptr JSONSaver::objectToJson(
    const shared_ptr<Object> object) {
  Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
  json->set("id", std::to_string(object->getId()));
  json->set("name", object->getName());

  if (object->getClass())
    json->set("class", std::to_string(object->getClass()->getId()));
  else
    json->set("class", std::string("no_class"));

  Poco::JSON::Array::Ptr attributes = new Poco::JSON::Array;
  for (std::shared_ptr<Attribute> attribute : object->getAttributes()) {
    attributes->add(attributeToJson(attribute));
  }
  json->set("attributes", attributes);

  Poco::JSON::Array::Ptr annotations = new Poco::JSON::Array;

  for (auto& pair : object->getAnnotations()) {
    annotations->add(std::to_string(pair.second.lock()->getId()));
  }
  json->set("annotations", annotations);

  Poco::JSON::Array::Ptr frames = new Poco::JSON::Array;

  for (auto frame : object->getFrames()) {
    frames->add(std::to_string(frame->getFrameNumber()));
  }
  json->set("frames", frames);

  return json;
}

Poco::JSON::Object::Ptr JSONSaver::classToJson(const shared_ptr<Class> c) {
  Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
  json->set("id", std::to_string(c->getId()));
  json->set("name", c->getName());
  return json;
}

void JSONSaver::save() {
  std::ofstream ostr(this->path, std::ios::out);
  this->session.get()->stringify(ostr, 1);
}

// static attributes (if any)

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of JSONSaver class body
 ************************************************************/
