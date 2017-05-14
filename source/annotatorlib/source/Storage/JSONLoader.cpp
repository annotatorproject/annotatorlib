// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Loader_JSONLoader_BODY

/************************************************************
 JSONLoader class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>
#include <AnnotatorLib/Storage/JSONLoader.h>

#include <memory>

#include <Poco/Dynamic/Var.h>
#include <Poco/File.h>
#include <Poco/FileStream.h>
#include <Poco/JSON/Handler.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Stringifier.h>
#include <Poco/Path.h>

using std::shared_ptr;

namespace AnnotatorLib {
namespace Storage {

void JSONLoader::setPath(std::string path) { this->path = path; }

StorageType JSONLoader::getType() { return StorageType::JSON; }

void JSONLoader::loadSession(Session *session) {
  Poco::Path path(this->path);
  Poco::File file(path);

  if (file.exists()) {
    Poco::FileInputStream fis(this->path);
    Poco::JSON::Parser parser;
    parser.parse(fis);
    Poco::Dynamic::Var result = parser.result();
    Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();
    try {
      loadAttributes(json, session);
      loadClasses(json, session);
      loadObjects(json, session);
      loadFrames(json, session);
      loadAnnotations(json, session);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << e.message() << std::endl << std::endl;
    }
  }
}

std::shared_ptr<Attribute> JSONLoader::loadAttribute(
    Poco::JSON::Object::Ptr value) {
  unsigned long id = std::stoul(value->get("id").extract<std::string>());
  std::string name = value->get("name").extract<std::string>();
  std::string type = value->get("type").extract<std::string>();

  // TODO: default value
  AttributeType t = AttributeTypeFromString(type);
  std::shared_ptr<Attribute> a = std::make_shared<Attribute>(id, t, name);
  std::shared_ptr<AttributeValue> av;
  switch (t) {
    case AttributeType::STRING:
      av = std::make_shared<AttributeValue>(
          value->get("value").extract<std::string>());
      break;
    case AttributeType::INTEGER:
      av =
          std::make_shared<AttributeValue>(value->get("value").extract<long>());
      break;
    case AttributeType::FLOAT:
      av = std::make_shared<AttributeValue>(
          value->get("value").extract<double>());
      break;
    case AttributeType::BOOLEAN:
      av = std::make_shared<AttributeValue>(
          value->get("value").extract<std::string>() == "true");

      break;
    default:
      av = std::make_shared<AttributeValue>(
          value->get("value").extract<std::string>());
  };
  a->setValue(av);
  return a;
}

void JSONLoader::loadAttributes(Poco::JSON::Object::Ptr json,
                                Session *session) {
  if (!json->has("attributes")) return;
  Poco::JSON::Array::Ptr array = json->getArray("attributes");

  for (std::size_t i = 0; i < array->size(); ++i) {
    Poco::JSON::Object::Ptr value = array->getObject(i);
    session->addAttribute(loadAttribute(value));
  }
}

void JSONLoader::loadAnnotations(Poco::JSON::Object::Ptr json,
                                 Session *session) {
  if (!json->has("annotations")) return;
  Poco::JSON::Array::Ptr array = json->getArray("annotations");

  for (std::size_t i = 0; i < array->size(); ++i) {
    Poco::JSON::Object::Ptr value = array->getObject(i);
    unsigned long object =
        std::stoul(value->get("object").extract<std::string>());
    unsigned long frame =
        std::stoul(value->get("frame").extract<std::string>());
    float x = std::stof(value->get("x").extract<std::string>());
    float y = std::stof(value->get("y").extract<std::string>());
    float width = std::stof(value->get("width").extract<std::string>());
    float height = std::stof(value->get("height").extract<std::string>());
    AnnotationType type =
        AnnotationTypeFromString(value->get("type").extract<std::string>());

    shared_ptr<Object> o = session->getObject(object);
    shared_ptr<Frame> f = session->getFrame(frame);

    if (o && f) {
      shared_ptr<Annotation> a = Annotation::make_shared(f, o, type);
      a->setPosition(x, y, width, height);
      // add attributes
      if (value->has("attributes") && !value->isNull("attributes")) {
        Poco::JSON::Array::Ptr attrArray = value->getArray("attributes");

        for (std::size_t i = 0; i < attrArray->size(); ++i) {
          Poco::JSON::Object::Ptr attrValue = attrArray->getObject(i);
          a->addAttribute(loadAttribute(attrValue));
        }
      }
      session->addAnnotation(a);
    }
  }
}

void JSONLoader::loadClasses(Poco::JSON::Object::Ptr json, Session *session) {
  if (!json->has("classes")) return;
  Poco::JSON::Array::Ptr array = json->getArray("classes");

  for (std::size_t i = 0; i < array->size(); ++i) {
    Poco::JSON::Object::Ptr value = array->getObject(i);
    unsigned long id = std::stoul(value->get("id").extract<std::string>());
    std::string name = value->get("name").extract<std::string>();
    shared_ptr<Class> c = std::make_shared<Class>(id, name);
    session->addClass(c);
  }
}

void JSONLoader::loadObjects(Poco::JSON::Object::Ptr json, Session *session) {
  if (!json->has("objects")) return;
  Poco::JSON::Array::Ptr array = json->getArray("objects");

  for (std::size_t i = 0; i < array->size(); ++i) {
    Poco::JSON::Object::Ptr value = array->getObject(i);
    unsigned long id = std::stoul(value->get("id").extract<std::string>());
    std::string name = value->get("name").extract<std::string>();

    shared_ptr<Object> o = std::make_shared<Object>(id);
    o->setName(name);

    if (value->has("class")) {
      std::string class_id = value->get("class").extract<std::string>();

      if (class_id != "no_class") {
        o->setClass(session->getClass(std::stoul(class_id)));
      }
    }

    if (value->has("attributes") && !value->isNull("attributes")) {
      Poco::JSON::Array::Ptr attrArray = value->getArray("attributes");

      for (std::size_t i = 0; i < attrArray->size(); ++i) {
        Poco::JSON::Object::Ptr attrValue = attrArray->getObject(i);
        o->addAttribute(loadAttribute(attrValue));
      }
    }

    session->addObject(o);
  }
}

void JSONLoader::loadFrames(Poco::JSON::Object::Ptr json, Session *session) {
  if (!json->has("frames")) return;
  Poco::JSON::Array::Ptr array = json->getArray("frames");

  for (std::size_t i = 0; i < array->size(); ++i) {
    Poco::JSON::Object::Ptr value = array->getObject(i);
    unsigned long number =
        std::stoul(value->get("number").extract<std::string>());
    shared_ptr<Frame> f = std::make_shared<Frame>(number);
    session->addFrame(f);
  }
}

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of JSONLoader class body
 ************************************************************/
