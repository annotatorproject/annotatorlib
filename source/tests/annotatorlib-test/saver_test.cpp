
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Saver/AbstractSaver.h>
#include <AnnotatorLib/Saver/SaverFactory.h>
#include <AnnotatorLib/Session.h>
#include <gmock/gmock.h>

#include <string>

class saver_test : public testing::Test {
 public:
};

AnnotatorLib::Session initSession() {
  AnnotatorLib::Session session;
  AnnotatorLib::Frame *frame = new AnnotatorLib::Frame(1);
  session.addFrame(frame);

  AnnotatorLib::Frame *frame1 = new AnnotatorLib::Frame(4);
  session.addFrame(frame1);

  AnnotatorLib::Frame *frame2 = new AnnotatorLib::Frame(5);
  session.addFrame(frame2);

  AnnotatorLib::Frame *frame3 = new AnnotatorLib::Frame(15);
  session.addFrame(frame3);

  AnnotatorLib::Frame *frame4 = new AnnotatorLib::Frame(20);
  session.addFrame(frame4);

  AnnotatorLib::Attribute *attribute = new AnnotatorLib::Attribute(
      AnnotatorLib::Attribute::genId(), AnnotatorLib::AttributeType::BOOLEAN,
      "light");
  AnnotatorLib::AttributeValue *defaultValue =
      new AnnotatorLib::AttributeValue(false);
  attribute->setDefaultValue(defaultValue);
  session.addAttribute(attribute);

  AnnotatorLib::Object *object =
      new AnnotatorLib::Object(AnnotatorLib::Object::genId());
  AnnotatorLib::Object *object2 =
      new AnnotatorLib::Object(AnnotatorLib::Object::genId());

  object->setName("testobject");
  object2->setName("testobject2");

  //object->addFrame(frame);

  AnnotatorLib::Class *c = new AnnotatorLib::Class("testclass");
  object->setClass(c);
  object2->setClass(c);
  session.addClass(c);

  AnnotatorLib::Annotation *annotation =
      new AnnotatorLib::Annotation(frame, object, AnnotatorLib::AnnotationType::RECTANGLE);
  annotation->setPosition(100, 100, 100, 100);
  annotation->addAttribute(attribute);

  AnnotatorLib::Annotation *annotation2 =
      new AnnotatorLib::Annotation(frame1, object2, AnnotatorLib::AnnotationType::RECTANGLE);
  annotation2->setPosition(200, 200, 200, 200);
  annotation2->addAttribute(attribute);

  AnnotatorLib::Annotation *annotation3 =
      new AnnotatorLib::Annotation(frame2, object2, AnnotatorLib::AnnotationType::RECTANGLE);
  annotation3->setPosition(300, 300, 300, 300);
  annotation3->addAttribute(attribute);

  AnnotatorLib::Annotation *annotation4 =
      new AnnotatorLib::Annotation(frame3, object2, AnnotatorLib::AnnotationType::ELLIPSE);
  annotation4->setPosition(400, 400, 400, 400);
  annotation4->addAttribute(attribute);

  annotation2->setNext(annotation3);
  annotation3->setPrevious(annotation2);
  annotation3->setNext(annotation4);
  annotation4->setPrevious(annotation3);

  object->addAnnotation(annotation);
  object2->addAnnotation(annotation2);
  object2->addAnnotation(annotation3);
  object2->addAnnotation(annotation4);

  session.addObject(object);
  session.addObject(object2);

  session.addAnnotation(annotation);
  session.addAnnotation(annotation2);
  session.addAnnotation(annotation3);
  session.addAnnotation(annotation4);
  session.addAttribute(attribute);
  return session;
}

TEST_F(saver_test, saveJson) {
  AnnotatorLib::Session session = initSession();
  AnnotatorLib::Saver::AbstractSaver *saver =
      AnnotatorLib::Saver::SaverFactory::createSaver("json");
  saver->setPath("savertest.json");

  saver->saveSession(&session);

  saver->close();
  delete saver;
}

TEST_F(saver_test, saveXML) {
  AnnotatorLib::Session session = initSession();
  AnnotatorLib::Saver::AbstractSaver *saver =
      AnnotatorLib::Saver::SaverFactory::createSaver("xml");
  saver->setPath("xml/");

  saver->saveSession(&session);

  saver->close();
  delete saver;
}

#ifdef WITH_SQLITE3
TEST_F(saver_test, saveSQLite) {
  AnnotatorLib::Session session = initSession();
  AnnotatorLib::Saver::AbstractSaver *saver =
      AnnotatorLib::Saver::SaverFactory::createSaver("sqlite");
  saver->setPath("savertest.sqlite");

  saver->saveSession(&session);

  saver->close();
  delete saver;
}
#endif
