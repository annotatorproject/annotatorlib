// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Loader_MySQLLoader_BODY

/************************************************************
 MySQLLoader class body
 ************************************************************/

// include associated header file
#include "MySQLLoader.h"

#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/Data/SessionPool.h>
#include <Poco/Data/Statement.h>
#include <Poco/Tuple.h>

using std::shared_ptr;
using namespace Poco::Data::Keywords;

void MySQLLoader::setPath(std::string path) { this->path = path; }

AnnotatorLib::StorageType MySQLLoader::getType() {
  return AnnotatorLib::StorageType::MYSQL;
}

void MySQLLoader::loadSession(AnnotatorLib::Session *session) {
  Poco::Data::MySQL::Connector::registerConnector();
  Poco::Data::SessionPool pool("MySQL", this->path);

  Poco::Data::Session sess(pool.get());

  loadAttributes(sess, session);
  loadClasses(sess, session);
  loadObjects(sess, session);
  loadFrames(sess, session);
  loadAnnotations(sess, session);
}

void MySQLLoader::loadAttributes(Poco::Data::Session &sqlSession,
                                 AnnotatorLib::Session *session) {
  Poco::Data::Statement statement(sqlSession);
}

void MySQLLoader::loadAnnotations(Poco::Data::Session &sqlSession,
                                  AnnotatorLib::Session *session) {
  typedef Poco::Tuple<unsigned long, unsigned long, unsigned long,
                      unsigned long, unsigned long, float, float, float, float,
                      std::string>
      AnnotationTuple;
  std::vector<AnnotationTuple> annotations;

  Poco::Data::Statement statement(sqlSession);
  statement
      << "SELECT `id`,`next`, `previous`,`object`, `frame`, `x`, `y`, `width`, "
         "`height`, `type` FROM `annotations`",
      into(annotations);
  statement.execute();

  for (AnnotationTuple at : annotations) {
    unsigned long object_id = at.get<3>();
    unsigned long frame_id = at.get<4>();

    float x = at.get<5>();
    float y = at.get<6>();
    float width = at.get<7>();
    float height = at.get<8>();
    AnnotatorLib::AnnotationType type =
        AnnotatorLib::AnnotationTypeFromString(at.get<9>());

    shared_ptr<AnnotatorLib::Object> o = session->getObject(object_id);
    shared_ptr<AnnotatorLib::Frame> f = session->getFrame(frame_id);

    if (o && f) {
      shared_ptr<AnnotatorLib::Annotation> a =
          AnnotatorLib::Annotation::make_shared(f, o, type);
      a->setPosition(x, y, width, height);
      session->addAnnotation(a);
      loadAnnotationAttributes(sqlSession, a);
    }
  }
}

void MySQLLoader::loadAnnotationAttributes(
    Poco::Data::Session &sqlSession,
    std::shared_ptr<AnnotatorLib::Annotation> annotation) {
  typedef Poco::Tuple<unsigned long, std::string, std::string, std::string,
                      unsigned long>
      AttributeTuple;
  std::vector<AttributeTuple> attributes;

  Poco::Data::Statement statement(sqlSession);
  unsigned long annotation_id = annotation->getId();
  statement << "SELECT `id`,`name`, `type`, `value`, `annotation_id` FROM "
               "`annotation_attributes` WHERE `annotation_id`=?",
      use(annotation_id), into(attributes);
  statement.execute();

  for (AttributeTuple attribute : attributes) {
    unsigned long id = attribute.get<0>();
    std::string name = attribute.get<1>();
    std::string type = attribute.get<2>();
    std::string value = attribute.get<3>();

    AnnotatorLib::AttributeType t = AnnotatorLib::AttributeTypeFromString(type);
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
}

void MySQLLoader::loadClasses(Poco::Data::Session &sqlSession,
                              AnnotatorLib::Session *session) {
  typedef Poco::Tuple<unsigned long, std::string> ClassTuple;
  std::vector<ClassTuple> classes;

  Poco::Data::Statement statement(sqlSession);
  statement << "SELECT `id`,`name` FROM `classes`", into(classes);
  statement.execute();

  for (ClassTuple c : classes) {
    unsigned long class_id = c.get<0>();
    AnnotatorLib::Class *c_ = new AnnotatorLib::Class(class_id, c.get<1>());
    session->addClass(shared_ptr<AnnotatorLib::Class>(c_));
  }
}

void MySQLLoader::loadObjectAttributes(
    Poco::Data::Session &sqlSession,
    std::shared_ptr<AnnotatorLib::Object> object) {
  typedef Poco::Tuple<unsigned long, std::string, std::string, std::string,
                      unsigned long>
      AttributeTuple;
  std::vector<AttributeTuple> attributes;

  Poco::Data::Statement statement(sqlSession);
  std::string object_id = std::to_string(object->getId());
  statement << "SELECT `id`,`name`, `type`, `value`, `object_id` FROM "
               "`object_attributes` WHERE `object_id`=?",
      use(object_id), into(attributes);
  statement.execute();

  for (AttributeTuple attribute : attributes) {
    unsigned long id = attribute.get<0>();
    std::string name = attribute.get<1>();
    std::string type = attribute.get<2>();
    std::string value = attribute.get<3>();

    AnnotatorLib::AttributeType t = AnnotatorLib::AttributeTypeFromString(type);
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
}

void MySQLLoader::loadObjects(Poco::Data::Session &sqlSession,
                              AnnotatorLib::Session *session) {
  typedef Poco::Tuple<unsigned long, std::string, unsigned long> ObjectTuple;
  std::vector<ObjectTuple> objects;
  Poco::Data::Statement statement(sqlSession);
  statement << "SELECT `id`,`name`,`class` FROM `objects`", into(objects);
  statement.execute();

  for (ObjectTuple o : objects) {
    unsigned long object_id = o.get<0>();
    std::string object_name = o.get<1>();
    unsigned long class_id = o.get<2>();

    std::shared_ptr<AnnotatorLib::Object> object =
        std::make_shared<AnnotatorLib::Object>(object_id);
    object->setName(object_name);

    object->setClass(session->getClass(class_id));
    session->addObject(object);
    loadObjectAttributes(sqlSession, object);
  }
}

void MySQLLoader::loadFrames(Poco::Data::Session &sqlSession,
                             AnnotatorLib::Session *session) {
  std::vector<unsigned long> frames;

  Poco::Data::Statement statement(sqlSession);
  statement << "SELECT `frame` FROM `annotations`", into(frames);
  statement.execute();

  for (unsigned long nmb : frames) {
    AnnotatorLib::Frame *frame = new AnnotatorLib::Frame(nmb);
    session->addFrame(shared_ptr<AnnotatorLib::Frame>(frame));
  }
}

// static attributes (if any)

/************************************************************
 End of MySQLLoader class body
 ************************************************************/
