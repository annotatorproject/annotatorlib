// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Loader_MySQLLoader_BODY

/************************************************************
 MySQLLoader class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/Loader/MySQLLoader.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/Data/SessionPool.h>
#include <Poco/Data/Statement.h>
#include <Poco/Tuple.h>

using std::shared_ptr;
using namespace Poco::Data::Keywords;

namespace AnnotatorLib {
namespace Loader {

void MySQLLoader::setPath(std::string path) { this->path = path; }

StorageType MySQLLoader::getType() { return AnnotatorLib::StorageType::MYSQL; }

void MySQLLoader::loadSession(Session *session) {
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
                                 Session *session) {
  Poco::Data::Statement statement(sqlSession);
}

void MySQLLoader::loadAnnotations(Poco::Data::Session &sqlSession,
                                  Session *session) {
  typedef Poco::Tuple<std::string, std::string, std::string, std::string, float,
                      float, float, float, std::string>
      AnnotationTuple;
  std::vector<AnnotationTuple> annotations;

  Poco::Data::Statement statement(sqlSession);
  statement << "SELECT `id`,`next`,`object`, `frame`, `x`, `y`, `width`, "
               "`height`, `type` FROM `annotations`",
      into(annotations);
  statement.execute();

  for (AnnotationTuple at : annotations) {
    unsigned long object_id = std::stol(at.get<2>());
    unsigned long frame_id = std::stol(at.get<3>());

    float x = at.get<4>();
    float y = at.get<5>();
    float width = at.get<6>();
    float height = at.get<7>();
    AnnotationType type = AnnotationTypeFromString(at.get<8>());

    shared_ptr<Object> o = session->getObject(object_id);
    shared_ptr<Frame> f = session->getFrame(frame_id);

    if (o && f) {
      shared_ptr<Annotation> a = Annotation::make_shared(f, o, type);
      a->setPosition(x, y, width, height);
      // TODO: add attributes

      session->addAnnotation(a);
    }
  }
}

void MySQLLoader::loadClasses(Poco::Data::Session &sqlSession,
                              Session *session) {
  typedef Poco::Tuple<std::string, std::string> ClassTuple;
  std::vector<ClassTuple> classes;

  Poco::Data::Statement statement(sqlSession);
  statement << "SELECT `id`,`name` FROM `classes`", into(classes);
  statement.execute();

  for (ClassTuple c : classes) {
    unsigned long class_id = std::stol(c.get<0>());
    AnnotatorLib::Class *c_ = new AnnotatorLib::Class(class_id, c.get<1>());
    session->addClass(shared_ptr<AnnotatorLib::Class>(c_));
  }
}

void MySQLLoader::loadObjects(Poco::Data::Session &sqlSession,
                              Session *session) {
  typedef Poco::Tuple<std::string, std::string, std::string> ObjectTuple;
  std::vector<ObjectTuple> objects;
  Poco::Data::Statement statement(sqlSession);
  statement << "SELECT `id`,`name`,`class` FROM `objects`", into(objects);
  statement.execute();

  for (ObjectTuple o : objects) {
    unsigned long object_id = std::stol(o.get<0>());
    std::string object_name = o.get<1>();
    unsigned long class_id = std::stol(o.get<2>());

    Object *object = new Object(object_id);
    object->setName(object_name);

    object->setClass(session->getClass(class_id));
    session->addObject(shared_ptr<Object>(object));
  }
}

void MySQLLoader::loadFrames(Poco::Data::Session &sqlSession,
                             Session *session) {
  std::vector<std::string> frames;

  Poco::Data::Statement statement(sqlSession);
  statement << "SELECT `frame` FROM `annotations`", into(frames);
  statement.execute();

  for (std::string f : frames) {
    unsigned long nmb = std::stol(f);
    Frame *frame = new Frame(nmb);
    session->addFrame(shared_ptr<Frame>(frame));
  }
}

// static attributes (if any)

} // of namespace Loader
} // of namespace AnnotatorLib

/************************************************************
 End of MySQLLoader class body
 ************************************************************/
