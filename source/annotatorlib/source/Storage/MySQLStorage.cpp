// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Storage_MySQLStorage_BODY

/************************************************************
 MySQLStorage class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/Loader/MySQLLoader.h>
#include <AnnotatorLib/Storage/MySQLSaver.h>
#include <AnnotatorLib/Storage/MySQLStorage.h>

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/Statement.h>

using Poco::Data::Session;
using Poco::Data::Statement;
using namespace Poco::Data::Keywords;

namespace AnnotatorLib {
namespace Storage {

void MySQLStorage::setPath(std::string path) { this->path = path; }

StorageType MySQLStorage::getType() { return AnnotatorLib::StorageType::MYSQL; }

bool MySQLStorage::addAnnotation(shared_ptr<Annotation> annotation,
                                 bool add_associated_objects) {
  AnnotatorLib::Session::addAnnotation(annotation, add_associated_objects);
  if (_open) {
    struct AnnotationStruct {
      unsigned long id;
      unsigned long next;
      unsigned long previous;
      unsigned long object;
      unsigned long frame;
      float x;
      float y;
      float width;
      float height;
      std::string type;
    };
    AnnotationStruct a_ = {
        annotation->getId(),
        0L,
        0L,
        annotation->getObject()->getId(),
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

    Poco::Data::Statement statement = getStatement();

    try {
      statement << "INSERT INTO `annotations` VALUES(?, ?, ?, ?, ?, ?, ?, "
                   "?, ?, ?);",
          use(a_.id), use(a_.next), use(a_.previous), use(a_.object),
          use(a_.frame), use(a_.x), use(a_.y), use(a_.width), use(a_.height),
          use(a_.type);
      statement.execute();
      insertOrUpdateAnnotationAttributes(annotation);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
  return true;
}

shared_ptr<Annotation> MySQLStorage::removeAnnotation(unsigned long id,
                                                      bool unregister) {
  if (_open) {
    Poco::Data::Statement statement = getStatement();
    try {
      statement << "DELETE FROM `annotations` WHERE `id`=" +
                       std::to_string(id) + ";";
      statement.execute();
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
  return AnnotatorLib::Session::removeAnnotation(id, unregister);
}

void MySQLStorage::updateAnnotation(shared_ptr<Annotation> annotation) {
  AnnotatorLib::Session::updateAnnotation(annotation);
  if (_open && getAnnotation(annotation->getId())) {
    struct AnnotationStruct {
      unsigned long id;
      unsigned long next;
      unsigned long previous;
      unsigned long object;
      unsigned long frame;
      float x;
      float y;
      float width;
      float height;
      std::string type;
    };
    AnnotationStruct a_ = {
        annotation->getId(),
        0L,
        0L,
        annotation->getObject()->getId(),
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

    Poco::Data::Statement statement = getStatement();

    try {
      statement
          << "UPDATE `annotations` SET `id`=?, `next`=?, `previous`=?, "
             "`object`=?, `frame`=?,"
             "`x`=?, `y`=?, `width`=?, `height`=?, `type`=? WHERE `id`=?;",
          use(a_.id), use(a_.next), use(a_.previous), use(a_.object),
          use(a_.frame), use(a_.x), use(a_.y), use(a_.width), use(a_.height),
          use(a_.type), use(a_.id);
      statement.execute();
      insertOrUpdateAnnotationAttributes(annotation);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
}

bool MySQLStorage::addClass(shared_ptr<Class> c) {
  AnnotatorLib::Session::addClass(c);
  if (_open) {
    struct ClassStruct {
      unsigned long id;
      std::string name;
    };
    ClassStruct c_ = {c->getId(), c->getName()};
    Poco::Data::Statement statement = getStatement();

    try {
      statement << "INSERT INTO `classes` VALUES(?, ?);", use(c_.id),
          use(c_.name);
      statement.execute();
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
  return true;
}

shared_ptr<Class> MySQLStorage::removeClass(Class *c) {
  if (_open) {
    Poco::Data::Statement statement = getStatement();
    try {
      statement << "DELETE FROM `classes` WHERE `id`=" +
                       std::to_string(c->getId()) + ";";
      statement.execute();
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }

  return AnnotatorLib::Session::removeClass(c);
}

void MySQLStorage::updateClass(shared_ptr<Class> theClass) {
  AnnotatorLib::Session::updateClass(theClass);
  if (_open && getClass(theClass->getId())) {
    struct ClassStruct {
      unsigned long id;
      std::string name;
    };
    ClassStruct c_ = {theClass->getId(), theClass->getName()};
    Poco::Data::Statement statement = getStatement();

    try {
      statement << "UPDATE `classes` SET `id`=?, `name`=? WHERE `id`=?;",
          use(c_.id), use(c_.name), use(c_.id);
      statement.execute();
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
}

bool MySQLStorage::addObject(shared_ptr<AnnotatorLib::Object> object,
                             bool add_associated_objects) {
  AnnotatorLib::Session::addObject(object, add_associated_objects);
  if (_open) {
    struct ObjectStruct {
      unsigned long id;
      std::string name;
      unsigned long _class;
    };
    ObjectStruct o_ = {object->getId(), object->getName(),
                       object->getClass()->getId()};
    Poco::Data::Statement statement = getStatement();

    try {
      statement << "INSERT INTO `objects` VALUES(?, ?, ?);", use(o_.id),
          use(o_.name), use(o_._class);
      statement.execute();
      insertOrUpdateObjectAttributes(object);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
  return true;
}

shared_ptr<Object> MySQLStorage::removeObject(unsigned long id,
                                              bool remove_annotations) {
  if (_open) {
    Poco::Data::Statement statement = getStatement();
    try {
      statement << "DELETE FROM `objects` WHERE `id`=" + std::to_string(id) +
                       ";";
      statement.execute();
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
  return AnnotatorLib::Session::removeObject(id, remove_annotations);
}

void MySQLStorage::updateObject(shared_ptr<Object> object) {
  AnnotatorLib::Session::updateObject(object);
  if (_open && getObject(object->getId())) {
    struct ObjectStruct {
      unsigned long id;
      std::string name;
      unsigned long _class;
    };
    ObjectStruct o_ = {object->getId(), object->getName(),
                       object->getClass()->getId()};
    Poco::Data::Statement statement = getStatement();

    try {
      statement
          << "UPDATE `objects` SET `id`=?, `name`=?, `class`=? WHERE `id`=?;",
          use(o_.id), use(o_.name), use(o_._class), use(o_.id);
      statement.execute();

      insertOrUpdateObjectAttributes(object);
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
}

MySQLStorage::~MySQLStorage() {
  if (pool) delete pool;
}

bool MySQLStorage::open() {
  Poco::Data::MySQL::Connector::registerConnector();
  pool = new Poco::Data::SessionPool("MySQL", this->path);
  createTables();

  AnnotatorLib::Loader::MySQLLoader loader;
  loader.setPath(this->path);
  loader.loadSession(this);

  this->_open = true;
  return _open;
}

bool MySQLStorage::isOpen() { return _open; }

bool MySQLStorage::flush() { return true; }

bool MySQLStorage::isSaved() { return true; }

bool MySQLStorage::close() {
  this->_open = false;
  return flush();
}

Poco::Data::Statement MySQLStorage::getStatement() {
  Poco::Data::Session sess(pool->get());
  return Poco::Data::Statement(sess);
}

void MySQLStorage::insertOrUpdateAnnotationAttributes(
    shared_ptr<Annotation> annotation) {
  struct AttributeStruct {
    unsigned long id;
    std::string name;
    std::string type;
    std::string value;
    unsigned long annotation_id;
  };

  for (std::shared_ptr<AnnotatorLib::Attribute> attribute :
       annotation->getAttributes()) {
    AttributeStruct a_ = {attribute->getId(), attribute->getName(),
                          AttributeTypeToString(attribute->getType()),
                          attribute->getValue()->toString(),
                          annotation->getId()};

    Poco::Data::Statement statement = getStatement();

    try {
      statement << "INSERT INTO `annotation_attributes` (`id`,`name`, `type`, "
                   "`value`, `annotation_id`) VALUES (?,?,?,?,?)"
                   "ON DUPLICATE KEY UPDATE `value`=? ;",
          use(a_.id), use(a_.name), use(a_.type), use(a_.value),
          use(a_.annotation_id), use(a_.value);
      statement.execute();
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
}

void MySQLStorage::insertOrUpdateObjectAttributes(shared_ptr<Object> object) {
  struct AttributeStruct {
    unsigned long id;
    std::string name;
    std::string type;
    std::string value;
    unsigned long object_id;
  };

  for (std::shared_ptr<AnnotatorLib::Attribute> attribute :
       object->getAttributes()) {
    AttributeStruct a_ = {attribute->getId(), attribute->getName(),
                          AttributeTypeToString(attribute->getType()),
                          attribute->getValue()->toString(), object->getId()};

    Poco::Data::Statement statement = getStatement();

    try {
      statement << "INSERT INTO `object_attributes` (`id`,`name`, `type`, "
                   "`value`, `object_id`) VALUES (?,?,?,?,?)"
                   "ON DUPLICATE KEY UPDATE `value`=? ;",
          use(a_.id), use(a_.name), use(a_.type), use(a_.value),
          use(a_.object_id), use(a_.value);
      statement.execute();
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << e.message() << std::endl;
    }
  }
}

void MySQLStorage::createTables() {
  Poco::Data::Statement statement = getStatement();

  statement << "CREATE TABLE IF NOT EXISTS `annotations` ( \
           `id` INT NOT NULL, \
            `next` INT NOT NULL, \
            `previous` INT NOT NULL, \
            `object` INT NOT NULL, \
            `frame` INT NOT NULL, \
            `x` float NOT NULL default 0, \
            `y` float NOT NULL default 0, \
           `width` float NOT NULL default 1, \
            `height` float NOT NULL default 1, \
            `type` char(16) NOT NULL, \
            PRIMARY KEY (`id`) \
            ) DEFAULT CHARSET=utf8;";
  statement.execute();

  statement = getStatement();

  statement << "CREATE TABLE IF NOT EXISTS `classes` ("
            << "`id` INT NOT NULL, "
            << "`name` varchar(256) NOT NULL,"
            << "PRIMARY KEY (`id`)"
            << ") DEFAULT CHARSET=utf8;";
  statement.execute();

  statement = getStatement();

  statement << "CREATE TABLE IF NOT EXISTS `objects` ("
            << "`id` INT NOT NULL, "
            << "`name` varchar(256) NOT NULL,"
            << "`class` INT NOT NULL,"
            << "PRIMARY KEY (`id`)"
            << ") DEFAULT CHARSET=utf8;";
  statement.execute();

  statement = getStatement();

  statement << "CREATE TABLE IF NOT EXISTS `object_attributes` ("
            << "`id` INT NOT NULL, "
            << "`name` varchar(256) NOT NULL,"
            << "`type` varchar(16) NOT NULL,"
            << "`value` varchar(4096) NOT NULL,"
            << "`object_id` INT NOT NULL, "
            << "PRIMARY KEY (`id`)"
            << ") DEFAULT CHARSET=utf8;";
  statement.execute();

  statement = getStatement();

  statement << "CREATE TABLE IF NOT EXISTS `annotation_attributes` ("
            << "`id` INT NOT NULL, "
            << "`name` varchar(256) NOT NULL,"
            << "`type` varchar(16) NOT NULL,"
            << "`value` varchar(4096) NOT NULL,"
            << "`annotation_id` INT NOT NULL, "
            << "PRIMARY KEY (`id`)"
            << ") DEFAULT CHARSET=utf8;";
  statement.execute();
}

// static attributes (if any)

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of MySQLStorage class body
 ************************************************************/
