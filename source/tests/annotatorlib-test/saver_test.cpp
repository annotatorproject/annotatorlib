// Copyright 2016 Annotator Team
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Saver/AbstractSaver.h>
#include <AnnotatorLib/Saver/SaverFactory.h>
#include <AnnotatorLib/Session.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

using namespace AnnotatorLib;
using std::shared_ptr;

class saver_test : public testing::Test {
 public:
};

Session* initSession() {
  Session* session = new Session();
  shared_ptr<Frame> frame1 = std::make_shared<Frame>(1);
  shared_ptr<Frame> frame4 = std::make_shared<Frame>(4);
  shared_ptr<Frame> frame5 = std::make_shared<Frame>(5);
  shared_ptr<Frame> frame15 = std::make_shared<Frame>(15);

  shared_ptr<Attribute> attribute = std::make_shared<Attribute>(
      Attribute::genId(), AttributeType::BOOLEAN, "light");
  AttributeValue* defaultValue = new AttributeValue(false);
  attribute->setValue(defaultValue);

  shared_ptr<Object> object1 = std::make_shared<Object>();
  shared_ptr<Object> object2 = std::make_shared<Object>();

  object1->setName("testobject");
  object2->setName("testobject2");

  shared_ptr<Class> c = std::make_shared<Class>("testclass");
  object1->setClass(c);
  object2->setClass(c);

  shared_ptr<Annotation> annotation1 =
      Annotation::make_shared(frame1, object1, AnnotationType::RECTANGLE);
  annotation1->setPosition(100, 100, 100, 100);
  annotation1->addAttribute(attribute);

  shared_ptr<Annotation> annotation2 =
      Annotation::make_shared(frame4, object2, AnnotationType::RECTANGLE);
  annotation2->setPosition(200, 200, 200, 200);
  annotation2->addAttribute(attribute);

  shared_ptr<Annotation> annotation3 =
      Annotation::make_shared(frame5, object2, AnnotationType::RECTANGLE);
  annotation3->setPosition(300, 300, 300, 300);
  annotation3->addAttribute(attribute);

  shared_ptr<Annotation> annotation4 =
      Annotation::make_shared(frame15, object2, AnnotationType::ELLIPSE);
  annotation4->setPosition(400, 400, 400, 400);
  annotation4->addAttribute(attribute);

  session->addAnnotation(shared_ptr<Annotation>(annotation1));
  session->addAnnotation(shared_ptr<Annotation>(annotation2));
  session->addAnnotation(shared_ptr<Annotation>(annotation3));
  session->addAnnotation(shared_ptr<Annotation>(annotation4));
  session->addAttribute(shared_ptr<Attribute>(attribute));

  return session;
}

TEST_F(saver_test, saveJson) {
  Session* session = initSession();
  Saver::AbstractSaver* saver = Saver::SaverFactory::createSaver("json");
  saver->setPath("savertest.json");
  saver->saveSession(session);

  saver->close();
  delete saver;
  delete session;
}

TEST_F(saver_test, saveXML) {
  Session* session = initSession();
  Saver::AbstractSaver* saver = Saver::SaverFactory::createSaver("xml");
  saver->setPath("xml/");
  saver->saveSession(session);
  saver->close();
  delete saver;
}

#ifdef WITH_SQLITE3
TEST_F(saver_test, saveSQLite) {
  Session session = initSession();
  Saver::AbstractSaver* saver = Saver::SaverFactory::createSaver("sqlite");
  saver->setPath("savertest.sqlite");

  saver->saveSession(&session);

  saver->close();
  delete saver;
}
#endif
