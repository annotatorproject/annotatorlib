#include <gmock/gmock.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/NewAnnotation.h>
#include <AnnotatorLib/Commands/UpdateObject.h>
#include <AnnotatorLib/Commands/RemoveObject.h>
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
