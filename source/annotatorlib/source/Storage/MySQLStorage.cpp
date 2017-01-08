// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Storage_MySQLStorage_BODY

/************************************************************
 MySQLStorage class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/Loader/MySQLLoader.h>
#include <AnnotatorLib/Saver/MySQLSaver.h>
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
    struct Annotation {
      std::string id;
      std::string next;
      std::string previous;
      std::string object;
      std::string frame;
      float x;
      float y;
      float width;
      float height;
      std::string type;
    };
    Annotation a_ = {
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

    Poco::Data::Statement statement = getStatement();

    try {
      statement << "INSERT INTO `annotations` VALUES(?, ?, ?, ?, ?, ?, ?, "
                   "?, ?, ?);",
          use(a_.id), use(a_.next), use(a_.previous), use(a_.object),
          use(a_.frame), use(a_.x), use(a_.y), use(a_.width), use(a_.height),
          use(a_.type);
      statement.execute();
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
      statement << "DELETE FROM `annotations` WHERE `id`='" +
                       std::to_string(id) + "';";
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
    struct Annotation {
      std::string id;
      std::string next;
      std::string previous;
      std::string object;
      std::string frame;
      float x;
      float y;
      float width;
      float height;
      std::string type;
    };
    Annotation a_ = {
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
      std::string id;
      std::string name;
    };
    ClassStruct c_ = {std::to_string(c->getId()), c->getName()};
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
      statement << "DELETE FROM `classes` WHERE `id`='" +
                       std::to_string(c->getId()) + "';";
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
      std::string id;
      std::string name;
    };
    ClassStruct c_ = {std::to_string(theClass->getId()), theClass->getName()};
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
      std::string id;
      std::string name;
      std::string _class;
    };
    ObjectStruct o_ = {std::to_string(object->getId()), object->getName(),
                       std::to_string(object->getClass()->getId())};
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
      statement << "DELETE FROM `objects` WHERE `id`='" + std::to_string(id) +
                       "';";
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
      std::string id;
      std::string name;
      std::string _class;
    };
    ObjectStruct o_ = {std::to_string(object->getId()), object->getName(),
                       std::to_string(object->getClass()->getId())};
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

void MySQLStorage::insertOrUpdateObjectAttributes(shared_ptr<Object> object) {
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
           `id` char(16) NOT NULL, \
            `next` char(16) NOT NULL, \
            `previous` char(16) NOT NULL, \
            `object` char(16) NOT NULL, \
            `frame` char(16) NOT NULL, \
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
            << "`id` char(16) NOT NULL, "
            << "`name` varchar(256) NOT NULL,"
            << "PRIMARY KEY (`id`)"
            << ") DEFAULT CHARSET=utf8;";
  statement.execute();

  statement = getStatement();

  statement << "CREATE TABLE IF NOT EXISTS `objects` ("
            << "`id` char(16) NOT NULL, "
            << "`name` varchar(256) NOT NULL,"
            << "`class` char(16) NOT NULL,"
            << "PRIMARY KEY (`id`)"
            << ") DEFAULT CHARSET=utf8;";
  statement.execute();

  statement = getStatement();

  statement << "CREATE TABLE IF NOT EXISTS `object_attributes` ("
            << "`id` char(16) NOT NULL, "
            << "`name` varchar(256) NOT NULL,"
            << "`type` varchar(16) NOT NULL,"
            << "`value` varchar(4096) NOT NULL,"
            << "`object_id` char(16) NOT NULL, "
            << "PRIMARY KEY (`id`)"
            << ") DEFAULT CHARSET=utf8;";
  statement.execute();

  statement = getStatement();

  statement << "CREATE TABLE IF NOT EXISTS `annotation_attributes` ("
            << "`id` char(16) NOT NULL, "
            << "`name` varchar(256) NOT NULL,"
            << "`type` varchar(16) NOT NULL,"
            << "`value` varchar(4096) NOT NULL,"
            << "`annotation_id` char(16) NOT NULL, "
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
