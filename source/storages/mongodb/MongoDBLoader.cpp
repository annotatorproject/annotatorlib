// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Loader_MongoDBLoader_BODY

/************************************************************
 MongoDBLoader class body
 ************************************************************/

// include associated header file
#include "MongoDBLoader.h"
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

#include <Poco/MongoDB/Array.h>
#include <Poco/MongoDB/Cursor.h>
#include <Poco/MongoDB/Database.h>
#include <Poco/URI.h>

using std::shared_ptr;

void MongoDBLoader::setPath(std::string path) { this->path = path; }

AnnotatorLib::StorageType MongoDBLoader::getType() {
  return AnnotatorLib::StorageType::MONGODB;
}

void MongoDBLoader::loadSession(AnnotatorLib::Session *session) {
  Poco::URI uri(path);
  Poco::MongoDB::Connection connection(
      uri.getHost(), (uri.getPort() == 0) ? 27017 : uri.getPort());
  dbname = uri.getPath();
  dbname.erase(0, 1);

  loadAttributes(connection, session);
  loadClasses(connection, session);
  loadObjects(connection, session);
  loadFrames(connection, session);
  loadAnnotations(connection, session);
}

void MongoDBLoader::loadAttributes(Poco::MongoDB::Connection &connection,
                                   AnnotatorLib::Session *session) {}

void MongoDBLoader::loadAnnotations(Poco::MongoDB::Connection &connection,
                                    AnnotatorLib::Session *session) {
  Poco::MongoDB::Cursor cursor(dbname, "annotations");

  Poco::MongoDB::ResponseMessage &response = cursor.next(connection);
  while (1) {
    for (Poco::MongoDB::Document::Vector::const_iterator it =
             response.documents().begin();
         it != response.documents().end(); ++it) {
      unsigned long object_id = (*it)->get<long>("object");
      unsigned long frame_id = (*it)->get<long>("frame");

      float x = (*it)->get<double>("x");
      float y = (*it)->get<double>("y");
      float width = (*it)->get<double>("width");
      float height = (*it)->get<double>("height");
      AnnotatorLib::AnnotationType type =
          AnnotatorLib::AnnotationTypeFromString(
              (*it)->get<std::string>("type"));

      shared_ptr<AnnotatorLib::Object> o = session->getObject(object_id);
      shared_ptr<AnnotatorLib::Frame> f = session->getFrame(frame_id);

      if (o && f) {
        shared_ptr<AnnotatorLib::Annotation> a =
            AnnotatorLib::Annotation::make_shared(f, o, type);
        a->setPosition(x, y, width, height);
        session->addAnnotation(a);
        loadAnnotationAttributes(connection, a);
      }
    }
    if (response.cursorID() == 0) {
      break;
    }
    response = cursor.next(connection);
  };
}

void MongoDBLoader::loadAnnotationAttributes(
    Poco::MongoDB::Connection &connection,
    std::shared_ptr<AnnotatorLib::Annotation> annotation) {
  Poco::MongoDB::Cursor cursor(dbname, "annotation_attributes");
  cursor.query().selector().add("annotation", (long)annotation->getId());

  Poco::MongoDB::ResponseMessage &response = cursor.next(connection);
  while (1) {
    for (Poco::MongoDB::Document::Vector::const_iterator it =
             response.documents().begin();
         it != response.documents().end(); ++it) {
      unsigned long id = (*it)->get<long>("id");
      std::string name = (*it)->get<std::string>("name");
      std::string type = (*it)->get<std::string>("type");
      std::string value = (*it)->get<std::string>("value");

      AnnotatorLib::AttributeType t =
          AnnotatorLib::AttributeTypeFromString(type);
      std::shared_ptr<AnnotatorLib::Attribute> a =
          std::make_shared<AnnotatorLib::Attribute>(id, t, name);
      std::shared_ptr<AnnotatorLib::AttributeValue> av;
      switch (t) {
        case AnnotatorLib::AttributeType::STRING:
          av = std::make_shared<AnnotatorLib::AttributeValue>(value);
          break;
        case AnnotatorLib::AttributeType::INTEGER:
          av = std::make_shared<AnnotatorLib::AttributeValue>(std::stol(value));
          break;
        case AnnotatorLib::AttributeType::FLOAT:
          av = std::make_shared<AnnotatorLib::AttributeValue>(std::stod(value));
          break;
        case AnnotatorLib::AttributeType::BOOLEAN:
          av = std::make_shared<AnnotatorLib::AttributeValue>(value == "true" ||
                                                              value == "True");
          break;
        default:
          av = std::make_shared<AnnotatorLib::AttributeValue>(value);
      };
      a->setValue(av);
      annotation->addAttribute(a);
    }
    if (response.cursorID() == 0) {
      break;
    }
    response = cursor.next(connection);
  };
}

void MongoDBLoader::loadClasses(Poco::MongoDB::Connection &connection,
                                AnnotatorLib::Session *session) {
  Poco::MongoDB::Cursor cursor(dbname, "classes");

  Poco::MongoDB::ResponseMessage &response = cursor.next(connection);
  while (1) {
    for (Poco::MongoDB::Document::Vector::const_iterator it =
             response.documents().begin();
         it != response.documents().end(); ++it) {
      unsigned long class_id = (*it)->get<long>("id");
      AnnotatorLib::Class *c_ =
          new AnnotatorLib::Class(class_id, (*it)->get<std::string>("name"));
      session->addClass(shared_ptr<AnnotatorLib::Class>(c_));
    }
    if (response.cursorID() == 0) {
      break;
    }
    response = cursor.next(connection);
  };
}

void MongoDBLoader::loadObjectAttributes(
    Poco::MongoDB::Connection &connection,
    std::shared_ptr<AnnotatorLib::Object> object) {
  Poco::MongoDB::Cursor cursor(dbname, "object_attributes");
  cursor.query().selector().add("object", (long)object->getId());

  Poco::MongoDB::ResponseMessage &response = cursor.next(connection);
  while (1) {
    for (Poco::MongoDB::Document::Vector::const_iterator it =
             response.documents().begin();
         it != response.documents().end(); ++it) {
      unsigned long id = (*it)->get<long>("id");
      std::string name = (*it)->get<std::string>("name");
      std::string type = (*it)->get<std::string>("type");
      std::string value = (*it)->get<std::string>("value");

      AnnotatorLib::AttributeType t =
          AnnotatorLib::AttributeTypeFromString(type);
      std::shared_ptr<AnnotatorLib::Attribute> a =
          std::make_shared<AnnotatorLib::Attribute>(id, t, name);
      std::shared_ptr<AnnotatorLib::AttributeValue> av;
      switch (t) {
        case AnnotatorLib::AttributeType::STRING:
          av = std::make_shared<AnnotatorLib::AttributeValue>(value);
          break;
        case AnnotatorLib::AttributeType::INTEGER:
          av = std::make_shared<AnnotatorLib::AttributeValue>(std::stol(value));
          break;
        case AnnotatorLib::AttributeType::FLOAT:
          av = std::make_shared<AnnotatorLib::AttributeValue>(std::stod(value));
          break;
        case AnnotatorLib::AttributeType::BOOLEAN:
          av = std::make_shared<AnnotatorLib::AttributeValue>(value == "true" ||
                                                              value == "True");
          break;
        default:
          av = std::make_shared<AnnotatorLib::AttributeValue>(value);
      };
      a->setValue(av);
      object->addAttribute(a);
    }
    if (response.cursorID() == 0) {
      break;
    }
    response = cursor.next(connection);
  };
}

void MongoDBLoader::loadObjects(Poco::MongoDB::Connection &connection,
                                AnnotatorLib::Session *session) {
  Poco::MongoDB::Cursor cursor(dbname, "objects");

  Poco::MongoDB::ResponseMessage &response = cursor.next(connection);
  while (1) {
    for (Poco::MongoDB::Document::Vector::const_iterator it =
             response.documents().begin();
         it != response.documents().end(); ++it) {
      unsigned long object_id = (*it)->get<long>("id");
      std::string object_name = (*it)->get<std::string>("name");
      unsigned long class_id = (*it)->get<long>("class");

      std::shared_ptr<AnnotatorLib::Object> object =
          std::make_shared<AnnotatorLib::Object>(object_id);
      object->setName(object_name);

      object->setClass(session->getClass(class_id));
      session->addObject(object);
      loadObjectAttributes(connection, object);
    }
    if (response.cursorID() == 0) {
      break;
    }
    response = cursor.next(connection);
  };
}

void MongoDBLoader::loadFrames(Poco::MongoDB::Connection &connection,
                               AnnotatorLib::Session *session) {
  Poco::MongoDB::Database db(dbname);
  Poco::SharedPtr<Poco::MongoDB::QueryRequest> command = db.createCommand();

  command->selector().add("distinct", "annotations").add("key", "frame");

  Poco::MongoDB::ResponseMessage response;
  connection.sendRequest(*command, response);
  if (response.hasDocuments()) {
    Poco::MongoDB::Array::Ptr values =
        response.documents()[0]->get<Poco::MongoDB::Array::Ptr>("values");
    for (unsigned int i = 0; i < values->size(); ++i) {
      unsigned long nmb = values->get<long>(i);
      session->addFrame(std::make_shared<AnnotatorLib::Frame>(nmb));
    }
  }
}

/************************************************************
 End of MongoDBLoader class body
 ************************************************************/
