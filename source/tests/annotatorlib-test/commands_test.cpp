#include <gmock/gmock.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/NewAnnotation.h>
#include <AnnotatorLib/Commands/UpdateObject.h>
#include <AnnotatorLib/Commands/RemoveObject.h>
#include <AnnotatorLib/Commands/CompressObject.h>
#include <AnnotatorLib/Project.h>
#include <string>

class commands_test : public testing::Test {
 public:
};

TEST_F(commands_test, newAnnotation) {
  AnnotatorLib::Session session;
  ASSERT_EQ(session.getAnnotations().size(), 0);

  AnnotatorLib::Frame* frame = new AnnotatorLib::Frame(1);
  session.addFrame(frame);
  AnnotatorLib::Class* c = new AnnotatorLib::Class("car");
  session.addClass(c);

  AnnotatorLib::Commands::NewAnnotation* nA =
      new AnnotatorLib::Commands::NewAnnotation(1001, c, frame, 10, 10, 5, 5,
                                                &session, false);
  session.execute(nA);
  ASSERT_EQ(session.getAnnotations().size(), 1);

  session.undo();
  ASSERT_EQ(session.getAnnotations().size(), 0);

  session.redo();
  ASSERT_EQ(session.getAnnotations().size(), 1);
  delete frame;
}

TEST_F(commands_test, updateObject) {
  AnnotatorLib::Session session;

  AnnotatorLib::Frame* frame = new AnnotatorLib::Frame(1);
  session.addFrame(frame);
  AnnotatorLib::Class* c = new AnnotatorLib::Class("car");
  session.addClass(c);

  AnnotatorLib::Commands::NewAnnotation* nA =
      new AnnotatorLib::Commands::NewAnnotation(1001, c, frame, 10, 10, 5, 5,
                                                &session, false);

  session.execute(nA);

  AnnotatorLib::Class* c_new = new AnnotatorLib::Class("person");
  session.addClass(c_new);

  AnnotatorLib::Commands::UpdateObject* uO =
      new AnnotatorLib::Commands::UpdateObject(session.getObject(1001), c_new);

  session.execute(uO);
  ASSERT_EQ(session.getAnnotations().size(), 1);
  ASSERT_EQ(session.getObjects().size(), 1);
  ASSERT_EQ(session.getObject(1001)->getClass()->getName(), "person");

  session.undo();
  ASSERT_EQ(session.getObject(1001)->getClass()->getName(), "car");
  ASSERT_EQ(session.getAnnotations().size(), 1);
  ASSERT_EQ(session.getObjects().size(), 1);

  session.redo();
  ASSERT_EQ(session.getObject(1001)->getClass()->getName(), "person");
  ASSERT_EQ(session.getAnnotations().size(), 1);
  ASSERT_EQ(session.getObjects().size(), 1);
}

TEST_F(commands_test, removeObject) {
  AnnotatorLib::Session session;

  AnnotatorLib::Frame* frame = new AnnotatorLib::Frame(1);
  session.addFrame(frame);
  AnnotatorLib::Class* c = new AnnotatorLib::Class("car");
  session.addClass(c);

  AnnotatorLib::Commands::NewAnnotation* nA =
      new AnnotatorLib::Commands::NewAnnotation(1001, c, frame, 10, 10, 5, 5,
                                                &session, false);

  session.execute(nA);

  AnnotatorLib::Commands::RemoveObject* rO =
      new AnnotatorLib::Commands::RemoveObject(&session, session.getObject(1001));

  ASSERT_EQ(session.getAnnotations().size(), 1);
  ASSERT_EQ(session.getObjects().size(), 1);

  session.execute(rO);
  ASSERT_EQ(session.getAnnotations().size(), 0);
  ASSERT_EQ(session.getObjects().size(), 0);

  session.undo();
  ASSERT_EQ(session.getAnnotations().size(), 1);
  ASSERT_EQ(session.getObjects().size(), 1);

  session.redo();
  ASSERT_EQ(session.getAnnotations().size(), 0);
  ASSERT_EQ(session.getObjects().size(), 0);
}

TEST_F(commands_test, compressObject) {
  AnnotatorLib::Session session;
  AnnotatorLib::Object* obj = new AnnotatorLib::Object();

  for(unsigned long i = 0; i < 5; ++i) {
    AnnotatorLib::Frame* frame_i = new AnnotatorLib::Frame(i);
    AnnotatorLib::Annotation* a_i = new AnnotatorLib::Annotation(frame_i, obj);
    a_i->setPosition(i * 10, 40, 20, 20);
  }
  session.addObject(obj);

  ASSERT_EQ(obj->getAnnotations().size(), 5);

  AnnotatorLib::Commands::CompressObject* cmd = new AnnotatorLib::Commands::CompressObject(&session, obj);
  session.execute(cmd);

  ASSERT_EQ(obj->getAnnotations().size(), 2);

  session.undo();

  ASSERT_EQ(obj->getAnnotations().size(), 5);

  session.redo();

  ASSERT_EQ(obj->getAnnotations().size(), 2);
}
