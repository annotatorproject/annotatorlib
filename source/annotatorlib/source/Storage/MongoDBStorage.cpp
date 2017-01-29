// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Storage_MySQLStorage_BODY

/************************************************************
 MongoDBStorage class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/Storage/MongoDBStorage.h>

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/Statement.h>
#include <Poco/URI.h>

#include <Poco/MongoDB/Array.h>
#include <Poco/MongoDB/Connection.h>
#include <Poco/MongoDB/Cursor.h>
#include <Poco/MongoDB/Database.h>
#include <Poco/MongoDB/MongoDB.h>

using Poco::Data::Session;
using Poco::Data::Statement;
using namespace Poco::Data::Keywords;

namespace AnnotatorLib {
namespace Storage {

void MongoDBStorage::setPath(std::string path) { this->path = path; }

StorageType MongoDBStorage::getType() {
  return AnnotatorLib::StorageType::MONGODB;
}

bool MongoDBStorage::addAnnotation(shared_ptr<Annotation> annotation,
                                   bool add_associated_objects) {
  AnnotatorLib::Session::addAnnotation(annotation, add_associated_objects);
  if (_open) {
    struct AnnotationStruct {
      std::string id;
      std::string next;
      std::string previous;
      std::string object;
      std::string frame;
      double x;
      double y;
      double width;
      double height;
      std::string type;
    };
    AnnotationStruct a_ = {
        std::to_string(annotation->getId()),
        "0",
        "0",
        std::to_string(annotation->getObject()->getId()),
        "0",
        annotation->getX(),
        annotation->getY(),
        annotation->getWidth(),
        annotation->getHeight(),
        AnnotatorLib::AnnotationTypeToString(annotation->getType())};
    if (annotation->getNext())
      a_.next = std::to_string(annotation->getNext()->getId());
    if (annotation->getPrevious())
      a_.previous = std::to_string(annotation->getPrevious()->getId());
    if (annotation->getFrame())
      a_.frame = std::to_string(annotation->getFrame()->getId());

    try {
      Poco::SharedPtr<Poco::MongoDB::InsertRequest> insertRequest =
          getDatabase().createInsertRequest("annotations");
      insertRequest->addNewDocument()
          .add("id", a_.id)
          .add("next", a_.next)
          .add("previous", a_.previous)
          .add("object", a_.object)
          .add("frame", a_.frame)
          .add("x", a_.x)
          .add("y", a_.y)
          .add("width", a_.width)
          .add("height", a_.height)
          .add("type", a_.type);

      connection->sendRequest(*insertRequest);

      std::string lastError = getDatabase().getLastError(*connection);
      if (!lastError.empty()) {
        std::cout << "Last Error: " << getDatabase().getLastError(*connection)
                  << std::endl;
      }
      insertOrUpdateAnnotationAttributes(annotation);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
  return true;
}

shared_ptr<Annotation> MongoDBStorage::removeAnnotation(unsigned long id,
                                                        bool unregister) {
  if (_open) {
    try {
      Poco::SharedPtr<Poco::MongoDB::DeleteRequest> request =
          getDatabase().createDeleteRequest("annotations");
      request->selector().add("id", std::to_string(id));

      connection->sendRequest(*request);

    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
  return AnnotatorLib::Session::removeAnnotation(id, unregister);
}

void MongoDBStorage::updateAnnotation(shared_ptr<Annotation> annotation) {
  AnnotatorLib::Session::updateAnnotation(annotation);
  if (_open && getAnnotation(annotation->getId())) {
    struct AnnotationStruct {
      std::string id;
      std::string next;
      std::string previous;
      std::string object;
      std::string frame;
      double x;
      double y;
      double width;
      double height;
      std::string type;
    };
    AnnotationStruct a_ = {
        std::to_string(annotation->getId()),
        "0",
        "0",
        std::to_string(annotation->getObject()->getId()),
        "0",
        annotation->getX(),
        annotation->getY(),
        annotation->getWidth(),
        annotation->getHeight(),
        AnnotatorLib::AnnotationTypeToString(annotation->getType())};
    if (annotation->getNext())
      a_.next = std::to_string(annotation->getNext()->getId());
    if (annotation->getPrevious())
      a_.previous = std::to_string(annotation->getPrevious()->getId());
    if (annotation->getFrame())
      a_.frame = std::to_string(annotation->getFrame()->getId());

    try {
      Poco::SharedPtr<Poco::MongoDB::UpdateRequest> request =
          getDatabase().createUpdateRequest("annotations");
      request->selector().add("id", a_.id);

      request->update()
          .addNewDocument("$set")
          .add("next", a_.next)
          .add("previous", a_.previous)
          .add("object", a_.object)
          .add("frame", a_.frame)
          .add("x", a_.x)
          .add("y", a_.y)
          .add("width", a_.width)
          .add("height", a_.height)
          .add("type", a_.type);

      connection->sendRequest(*request);

      insertOrUpdateAnnotationAttributes(annotation);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
}

bool MongoDBStorage::addClass(shared_ptr<Class> c) {
  AnnotatorLib::Session::addClass(c);
  if (_open) {
    struct ClassStruct {
      std::string id;
      std::string name;
    };
    ClassStruct c_ = {std::to_string(c->getId()), c->getName()};

    try {
      Poco::SharedPtr<Poco::MongoDB::InsertRequest> insertRequest =
          getDatabase().createInsertRequest("classes");
      insertRequest->addNewDocument().add("id", c_.id).add("name", c_.name);

      connection->sendRequest(*insertRequest);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
  return true;
}

shared_ptr<Class> MongoDBStorage::removeClass(Class *c) {
  if (_open) {
    try {
      Poco::SharedPtr<Poco::MongoDB::DeleteRequest> request =
          getDatabase().createDeleteRequest("classes");
      request->selector().add("id", std::to_string(c->getId()));
      connection->sendRequest(*request);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }

  return AnnotatorLib::Session::removeClass(c);
}

void MongoDBStorage::updateClass(shared_ptr<Class> theClass) {
  AnnotatorLib::Session::updateClass(theClass);
  if (_open && getClass(theClass->getId())) {
    struct ClassStruct {
      std::string id;
      std::string name;
    };
    ClassStruct c_ = {std::to_string(theClass->getId()), theClass->getName()};

    try {
      Poco::SharedPtr<Poco::MongoDB::UpdateRequest> request =
          getDatabase().createUpdateRequest("classes");
      request->selector().add("id", c_.id);

      request->update().addNewDocument("$set").add("name", c_.name);

      connection->sendRequest(*request);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
}

bool MongoDBStorage::addObject(shared_ptr<AnnotatorLib::Object> object,
                               bool add_associated_objects) {
  AnnotatorLib::Session::addObject(object, add_associated_objects);
  if (_open) {
    struct ObjectStruct {
      std::string id;
      std::string name;
      std::string _class;
    };
    ObjectStruct o_ = {std::to_string(object->getId()), object->getName(),
                       std::to_string(object->getClass()->getId())};

    try {
      Poco::SharedPtr<Poco::MongoDB::InsertRequest> insertRequest =
          getDatabase().createInsertRequest("objects");
      insertRequest->addNewDocument()
          .add("id", o_.id)
          .add("name", o_.name)
          .add("class", o_._class);

      connection->sendRequest(*insertRequest);
      insertOrUpdateObjectAttributes(object);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
  return true;
}

shared_ptr<Object> MongoDBStorage::removeObject(unsigned long id,
                                                bool remove_annotations) {
  if (_open) {
    try {
      Poco::SharedPtr<Poco::MongoDB::DeleteRequest> request =
          getDatabase().createDeleteRequest("objects");
      request->selector().add("id", std::to_string(id));
      connection->sendRequest(*request);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
  return AnnotatorLib::Session::removeObject(id, remove_annotations);
}

void MongoDBStorage::updateObject(shared_ptr<Object> object) {
  AnnotatorLib::Session::updateObject(object);
  if (_open && getObject(object->getId())) {
    struct ObjectStruct {
      std::string id;
      std::string name;
      std::string _class;
    };
    ObjectStruct o_ = {std::to_string(object->getId()), object->getName(),
                       std::to_string(object->getClass()->getId())};

    try {
      Poco::SharedPtr<Poco::MongoDB::UpdateRequest> request =
          getDatabase().createUpdateRequest("objects");
      request->selector().add("id", o_.id);

      request->update()
          .addNewDocument("$set")
          .add("name", o_.name)
          .add("class", o_._class);

      connection->sendRequest(*request);

      insertOrUpdateObjectAttributes(object);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
}

MongoDBStorage::~MongoDBStorage() {
  if (connection) delete connection;
}

bool MongoDBStorage::open() {
  Poco::URI uri(path);
  connection = new Poco::MongoDB::Connection(uri.getHost(), uri.getPort());
  dbname = uri.getPath();

  this->_open = true;
  return _open;
}

bool MongoDBStorage::isOpen() { return _open; }

bool MongoDBStorage::flush() { return true; }

bool MongoDBStorage::isSaved() { return true; }

bool MongoDBStorage::close() {
  this->_open = false;
  return flush();
}

void MongoDBStorage::insertOrUpdateAnnotationAttributes(
    shared_ptr<Annotation> annotation) {
  struct AttributeStruct {
    std::string id;
    std::string name;
    std::string type;
    std::string value;
    std::string annotation_id;
  };

  for (std::shared_ptr<AnnotatorLib::Attribute> attribute :
       annotation->getAttributes()) {
    AttributeStruct a_ = {
        std::to_string(attribute->getId()), attribute->getName(),
        AttributeTypeToString(attribute->getType()),
        attribute->getValue()->toString(), std::to_string(annotation->getId())};

    try {
      // TODO insert or update
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
}

void MongoDBStorage::insertOrUpdateObjectAttributes(shared_ptr<Object> object) {
  struct AttributeStruct {
    std::string id;
    std::string name;
    std::string type;
    std::string value;
    std::string object_id;
  };

  for (std::shared_ptr<AnnotatorLib::Attribute> attribute :
       object->getAttributes()) {
    AttributeStruct a_ = {
        std::to_string(attribute->getId()), attribute->getName(),
        AttributeTypeToString(attribute->getType()),
        attribute->getValue()->toString(), std::to_string(object->getId())};

    try {
      // TODO insert or update
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
}

Poco::MongoDB::Database MongoDBStorage::getDatabase() {
  return Poco::MongoDB::Database(dbname);
}

// static attributes (if any)

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of MySQLStorage class body
 ************************************************************/
