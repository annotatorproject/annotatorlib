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
#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/Statement.h>

// Derived includes directives

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
      std::string object;
      float x;
      float y;
      float width;
      float height;
    };
    Annotation a_ = {std::to_string(annotation->getId()),
                     "0",
                     std::to_string(annotation->getObject()->getId()),
                     annotation->getX(),
                     annotation->getY(),
                     annotation->getWidth(),
                     annotation->getHeight()};
    if (annotation->getNext())
      a_.next = std::to_string(annotation->getId());

    Poco::Data::Statement statement = getStatement();

    try {
      statement
          << "INSERT IGNORE INTO `annotations` VALUES(?, ?, ?, ?, ?, ?, ?);",
          use(a_.id), use(a_.next), use(a_.object), use(a_.x), use(a_.y),
          use(a_.width), use(a_.height), now;
      statement.execute();
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
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
                       std::to_string(id) + "';",
          now;
      statement.execute();
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
    }
  }
  return AnnotatorLib::Session::removeAnnotation(id, unregister);
}

bool MySQLStorage::addClass(shared_ptr<Class> c) {
  AnnotatorLib::Session::addClass(c);
  if (_open) {
    struct Class {
      std::string id;
      std::string name;
    };
    Class c_ = {std::to_string(c->getId()), c->getName()};
    Poco::Data::Statement statement = getStatement();

    try {
      statement << "INSERT IGNORE INTO `classes` VALUES(?, ?);", use(c_.id),
          use(c_.name), now;
      statement.execute();
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
    }
  }
  return true;
}

shared_ptr<Class> MySQLStorage::removeClass(Class *c) {
  if (_open) {
    Poco::Data::Statement statement = getStatement();
    try {
      statement << "DELETE FROM `classes` WHERE `id`='" +
                       std::to_string(c->getId()) + "';",
          now;
      statement.execute();
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
    }
  }

  return AnnotatorLib::Session::removeClass(c);
}

bool MySQLStorage::addObject(shared_ptr<AnnotatorLib::Object> object,
                             bool add_associated_objects) {
  AnnotatorLib::Session::addObject(object, add_associated_objects);
  if (_open) {
    struct Object {
      std::string id;
      std::string name;
    };
    Object o_ = {std::to_string(object->getId()), object->getName()};
    Poco::Data::Statement statement = getStatement();

    try {
      statement << "INSERT IGNORE INTO `objects` VALUES(?, ?);", use(o_.id),
          use(o_.name), now;
      statement.execute();
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
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
                       "';",
          now;
      statement.execute();
    } catch (Poco::Exception &e) {
      std::cout << e.what() << std::endl;
    }
  }
  return AnnotatorLib::Session::removeObject(id, remove_annotations);
}

bool MySQLStorage::open() {
  Poco::Data::MySQL::Connector::registerConnector();
  pool = new Poco::Data::SessionPool("MySQL", this->path);
  createTables();
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

void MySQLStorage::createTables() {
  Poco::Data::Statement statement = getStatement();

  statement << "CREATE TABLE IF NOT EXISTS `annotations` ( \
           `id` char(16) NOT NULL, \
            `next` char(16) NOT NULL, \
            `object` char(16) NOT NULL, \
            `x` float NOT NULL default 0, \
            `y` float NOT NULL default 0, \
           `width` float NOT NULL default 1, \
            `height` float NOT NULL default 1, \
            PRIMARY KEY (`id`) \
            ) DEFAULT CHARSET=utf8;",
      Poco::Data::Keywords::now;
  statement.execute();

  statement = getStatement();

  statement << "CREATE TABLE IF NOT EXISTS `classes` ("
            << "`id` char(16) NOT NULL, "
            << "`name` varchar(256) NOT NULL,"
            << "PRIMARY KEY (`id`)"
            << ") DEFAULT CHARSET=utf8;",
      Poco::Data::Keywords::now;
  statement.execute();

  statement = getStatement();

  statement << "CREATE TABLE IF NOT EXISTS `objects` ("
            << "`id` char(16) NOT NULL, "
            << "`name` varchar(256) NOT NULL,"
            << "PRIMARY KEY (`id`)"
            << ") DEFAULT CHARSET=utf8;",
      Poco::Data::Keywords::now;
  statement.execute();
}

// static attributes (if any)

} // of namespace Storage
} // of namespace AnnotatorLib

/************************************************************
 End of MySQLStorage class body
 ************************************************************/
