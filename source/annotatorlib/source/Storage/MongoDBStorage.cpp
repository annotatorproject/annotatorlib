// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Storage_MongoDBStorage_BODY

/************************************************************
 MongoDBStorage class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/Loader/MongoDBLoader.h>
#include <AnnotatorLib/Storage/MongoDBStorage.h>

#include <Poco/MongoDB/Array.h>
#include <Poco/MongoDB/Connection.h>
#include <Poco/MongoDB/Cursor.h>
#include <Poco/MongoDB/Database.h>
#include <Poco/MongoDB/MongoDB.h>
#include <Poco/URI.h>

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
      long id;
      long next;
      long previous;
      long object;
      long frame;
      double x;
      double y;
      double width;
      double height;
      std::string type;
    };
    AnnotationStruct a_ = {
        (long)annotation->getId(),
        0L,
        0L,
        (long)annotation->getObject()->getId(),
        0L,
        annotation->getX(),
        annotation->getY(),
        annotation->getWidth(),
        annotation->getHeight(),
        AnnotatorLib::AnnotationTypeToString(annotation->getType())};
    if (annotation->getNext()) a_.next = annotation->getNext()->getId();
    if (annotation->getPrevious())
      a_.previous = annotation->getPrevious()->getId();
    if (annotation->getFrame()) a_.frame = annotation->getFrame()->getId();

    try {
      Poco::MongoDB::Database db(dbname);
      Poco::SharedPtr<Poco::MongoDB::InsertRequest> insertRequest =
          db.createInsertRequest("annotations");
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

      std::cout << insertRequest->documents().size() << std::endl;

      connection->sendRequest(*insertRequest);

      std::string lastError = db.getLastError(*connection);
      if (!lastError.empty()) {
        std::cout << "Last Error: " << db.getLastError(*connection)
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
      Poco::MongoDB::Database db(dbname);
      Poco::SharedPtr<Poco::MongoDB::DeleteRequest> request =
          db.createDeleteRequest("annotations");
      request->selector().add("id", (long)id);

      connection->sendRequest(*request);
      std::string lastError = db.getLastError(*connection);
      if (!lastError.empty()) {
        std::cout << "Last Error: " << db.getLastError(*connection)
                  << std::endl;
      }

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
      long id;
      long next;
      long previous;
      long object;
      long frame;
      double x;
      double y;
      double width;
      double height;
      std::string type;
    };
    AnnotationStruct a_ = {
        (long)annotation->getId(),
        0L,
        0L,
        (long)annotation->getObject()->getId(),
        0L,
        annotation->getX(),
        annotation->getY(),
        annotation->getWidth(),
        annotation->getHeight(),
        AnnotatorLib::AnnotationTypeToString(annotation->getType())};
    if (annotation->getNext()) a_.next = annotation->getNext()->getId();
    if (annotation->getPrevious())
      a_.previous = annotation->getPrevious()->getId();
    if (annotation->getFrame()) a_.frame = annotation->getFrame()->getId();

    try {
      Poco::MongoDB::Database db(dbname);
      Poco::SharedPtr<Poco::MongoDB::UpdateRequest> request =
          db.createUpdateRequest("annotations");
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
      std::string lastError = db.getLastError(*connection);
      if (!lastError.empty()) {
        std::cout << "Last Error: " << db.getLastError(*connection)
                  << std::endl;
      }

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
      long id;
      std::string name;
    };
    ClassStruct c_ = {(long)c->getId(), c->getName()};

    try {
      Poco::MongoDB::Database db(dbname);
      Poco::SharedPtr<Poco::MongoDB::InsertRequest> insertRequest =
          db.createInsertRequest("classes");
      insertRequest->addNewDocument().add("id", c_.id).add("name", c_.name);

      connection->sendRequest(*insertRequest);
      std::string lastError = db.getLastError(*connection);
      if (!lastError.empty()) {
        std::cout << "Last Error: " << db.getLastError(*connection)
                  << std::endl;
      }
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
      Poco::MongoDB::Database db(dbname);
      Poco::SharedPtr<Poco::MongoDB::DeleteRequest> request =
          db.createDeleteRequest("classes");
      request->selector().add("id", (long)c->getId());
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
      long id;
      std::string name;
    };
    ClassStruct c_ = {(long)theClass->getId(), theClass->getName()};

    try {
      Poco::MongoDB::Database db(dbname);
      Poco::SharedPtr<Poco::MongoDB::UpdateRequest> request =
          db.createUpdateRequest("classes");
      request->selector().add("id", c_.id);

      request->update().addNewDocument("$set").add("name", c_.name);

      connection->sendRequest(*request);
      std::string lastError = db.getLastError(*connection);
      if (!lastError.empty()) {
        std::cout << "Last Error: " << db.getLastError(*connection)
                  << std::endl;
      }
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
      long id;
      std::string name;
      long _class;
    };
    ObjectStruct o_ = {(long)object->getId(), object->getName(),
                       (long)object->getClass()->getId()};

    try {
      Poco::MongoDB::Database db(dbname);
      Poco::SharedPtr<Poco::MongoDB::InsertRequest> insertRequest =
          db.createInsertRequest("objects");
      insertRequest->addNewDocument()
          .add("id", o_.id)
          .add("name", o_.name)
          .add("class", o_._class);

      connection->sendRequest(*insertRequest);
      std::string lastError = db.getLastError(*connection);
      if (!lastError.empty()) {
        std::cout << "Last Error: " << db.getLastError(*connection)
                  << std::endl;
      }
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
      Poco::MongoDB::Database db(dbname);
      Poco::SharedPtr<Poco::MongoDB::DeleteRequest> request =
          db.createDeleteRequest("objects");
      request->selector().add("id", (long)id);
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
      long id;
      std::string name;
      long _class;
    };
    ObjectStruct o_ = {(long)object->getId(), object->getName(),
                       (long)object->getClass()->getId()};

    try {
      Poco::MongoDB::Database db(dbname);
      Poco::SharedPtr<Poco::MongoDB::UpdateRequest> request =
          db.createUpdateRequest("objects");
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
  connection = new Poco::MongoDB::Connection(
      uri.getHost(), (uri.getPort() == 0) ? 27017 : uri.getPort());
  dbname = uri.getPath();
  dbname.erase(0, 1);

  AnnotatorLib::Loader::MongoDBLoader loader;
  loader.setPath(this->path);
  loader.loadSession(this);

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
    long id;
    std::string name;
    std::string type;
    std::string value;
    long annotation_id;
  };

  for (std::shared_ptr<AnnotatorLib::Attribute> attribute :
       annotation->getAttributes()) {
    AttributeStruct a_ = {(long)attribute->getId(), attribute->getName(),
                          AttributeTypeToString(attribute->getType()),
                          attribute->getValue()->toString(),
                          (long)annotation->getId()};

    try {
      Poco::MongoDB::Database db(dbname);
      Poco::SharedPtr<Poco::MongoDB::DeleteRequest> delRequest =
          db.createDeleteRequest("annotation_attributes");
      delRequest->selector().add("id", (long)a_.id);
      connection->sendRequest(*delRequest);

      Poco::SharedPtr<Poco::MongoDB::InsertRequest> insertRequest =
          db.createInsertRequest("annotation_attributes");
      insertRequest->addNewDocument()
          .add("id", a_.id)
          .add("name", a_.name)
          .add("type", a_.type)
          .add("value", a_.value)
          .add("annotation", a_.annotation_id);

      connection->sendRequest(*insertRequest);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
}

void MongoDBStorage::insertOrUpdateObjectAttributes(shared_ptr<Object> object) {
  struct AttributeStruct {
    long id;
    std::string name;
    std::string type;
    std::string value;
    long object_id;
  };

  for (std::shared_ptr<AnnotatorLib::Attribute> attribute :
       object->getAttributes()) {
    AttributeStruct a_ = {(long)attribute->getId(), attribute->getName(),
                          AttributeTypeToString(attribute->getType()),
                          attribute->getValue()->toString(),
                          (long)object->getId()};

    try {
      Poco::MongoDB::Database db(dbname);

      Poco::SharedPtr<Poco::MongoDB::DeleteRequest> delRequest =
          db.createDeleteRequest("object_attributes");
      delRequest->selector().add("id", (long)a_.id);
      connection->sendRequest(*delRequest);

      Poco::SharedPtr<Poco::MongoDB::InsertRequest> insertRequest =
          db.createInsertRequest("object_attributes");
      insertRequest->addNewDocument()
          .add("id", a_.id)
          .add("name", a_.name)
          .add("type", a_.type)
          .add("value", a_.value)
          .add("object", a_.object_id);

      connection->sendRequest(*insertRequest);

    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
}

// static attributes (if any)

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of MySQLStorage class body
 ************************************************************/
