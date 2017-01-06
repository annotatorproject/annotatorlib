// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Loader_JSONLoader_BODY

/************************************************************
 JSONLoader class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/Loader/JSONLoader.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <memory>

using std::shared_ptr;

namespace AnnotatorLib {
namespace Loader {

void JSONLoader::setPath(std::string path) { this->path = path; }

StorageType JSONLoader::getType() { return StorageType::JSON; }

void JSONLoader::loadSession(Session *session) {
  QFile file(QString::fromStdString(this->path));
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());

    QJsonObject json = document.object();
    loadAttributes(json, session);
    loadClasses(json, session);
    loadObjects(json, session);
    loadFrames(json, session);
    loadAnnotations(json, session);
  }
  file.close();
}

std::shared_ptr<Attribute> JSONLoader::loadAttribute(QJsonValue &value) {
  QJsonObject attribute = value.toObject();
  unsigned long id = attribute["id"].toString().toLong();
  QString name = attribute["name"].toString();
  QString type = attribute["type"].toString();

  // TODO: default value
  AttributeType t = AttributeTypeFromString(type.toStdString());
  std::shared_ptr<Attribute> a =
      std::make_shared<Attribute>(id, t, name.toStdString());
  std::shared_ptr<AttributeValue> av;
  switch (t) {
    case AttributeType::STRING:
      av = std::make_shared<AttributeValue>(
          attribute["value"].toString().toStdString());
      break;
    case AttributeType::INTEGER:
      av = std::make_shared<AttributeValue>(
          attribute["value"].toString().toLong());
      break;
    case AttributeType::FLOAT:
      av = std::make_shared<AttributeValue>(
          attribute["value"].toString().toDouble());
      break;
    case AttributeType::BOOLEAN:
      av = std::make_shared<AttributeValue>(attribute["value"].toBool());
      break;
    default:
      av = std::make_shared<AttributeValue>(
          attribute["value"].toString().toStdString());
  };
  a->setValue(av);
  return a;
}

void JSONLoader::loadAttributes(QJsonObject &json, Session *session) {
  QJsonArray attributes = json.value("attributes").toArray();
  for (QJsonValue value : attributes) {
    session->addAttribute(loadAttribute(value));
  }
}

void JSONLoader::loadClasses(QJsonObject &json, Session *session) {
  QJsonArray classes = json.value("classes").toArray();
  for (QJsonValue value : classes) {
    QJsonObject object = value.toObject();
    unsigned long id = object["id"].toString().toLong();
    QString name = object["name"].toString();
    Class *c = new Class(id, name.toStdString());

    session->addClass(shared_ptr<Class>(c));
  }
}

void JSONLoader::loadObjects(QJsonObject &json, Session *session) {
  QJsonArray objects = json.value("objects").toArray();
  for (QJsonValue value : objects) {
    QJsonObject object = value.toObject();
    unsigned long id = object["id"].toString().toLong();
    QString name = object["name"].toString();
    Object *o = new Object(id);
    o->setName(name.toStdString());

    if (object.contains("class")) {
      unsigned long class_id = object["class"].toString().toLong();
      o->setClass(session->getClass(
          class_id));  // TODO: get Class by Name (this is more efficient)
    }

    QJsonArray attributes = object.value("attributes").toArray();
    for (QJsonValue attribute : attributes) {
      o->addAttribute(loadAttribute(attribute));
      // unsigned long atid = attribute.toString().toLong();
      // if (session->getAttribute(atid))
      //  o->addAttribute(session->getAttribute(atid));
    }
    session->addObject(shared_ptr<Object>(o));
  }
}

void JSONLoader::loadFrames(QJsonObject &json, Session *session) {
  QJsonArray frames = json.value("frames").toArray();
  for (QJsonValue value : frames) {
    QJsonObject frame = value.toObject();
    unsigned long nmb = frame["number"].toString().toLong();
    Frame *f = new Frame(nmb);
    session->addFrame(shared_ptr<Frame>(f));
  }
}

void JSONLoader::loadAnnotations(QJsonObject &json, Session *session) {
  QJsonArray annotations = json.value("annotations").toArray();
  for (QJsonValue value : annotations) {
    QJsonObject annotation = value.toObject();
    // Note: id is now generated from frame and object id
    // unsigned long id = annotation["id"].toString().toLong();
    unsigned long object = annotation["object"].toString().toLong();
    unsigned long frame = annotation["frame"].toString().toLong();

    float x = annotation["x"].toString().toFloat();
    float y = annotation["y"].toString().toFloat();
    float width = annotation["width"].toString().toFloat();
    float height = annotation["height"].toString().toFloat();
    AnnotationType type =
        AnnotationTypeFromString(annotation["type"].toString().toStdString());

    shared_ptr<Object> o = session->getObject(object);
    shared_ptr<Frame> f = session->getFrame(frame);

    if (o && f) {
      shared_ptr<Annotation> a = Annotation::make_shared(f, o, type);
      a->setPosition(x, y, width, height);
      // add attributes
      QJsonArray attributes = annotation.value("attributes").toArray();
      for (QJsonValue attribute : attributes) {
        a->addAttribute(loadAttribute(attribute));
        // unsigned long atid = attribute.toString().toLong();
        // if (session->getAttribute(atid))
        //  a->addAttribute(session->getAttribute(atid));
      }
      session->addAnnotation(a);
    }
  }
}

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of JSONLoader class body
 ************************************************************/
