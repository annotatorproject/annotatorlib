#include <gmock/gmock.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/NewAnnotation.h>
#include <AnnotatorLib/Commands/NewObject.h>
#include <AnnotatorLib/Project.h>
#include <string>

class commands_test : public testing::Test {
 public:
};

TEST_F(commands_test, newObject) {
  AnnotatorLib::Session session;
  ASSERT_EQ(session.getObjects().size(), 0);
  AnnotatorLib::Commands::NewObject nO(&session);
  session.execute(&nO);
  ASSERT_EQ(session.getObjects().size(), 1);
  session.undo();
  ASSERT_EQ(session.getObjects().size(), 0);
  session.redo();
  ASSERT_EQ(session.getObjects().size(), 1);
}

TEST_F(commands_test, newAnnotation) {
  AnnotatorLib::Session session;
  ASSERT_EQ(session.getAnnotations().size(), 0);

  AnnotatorLib::Commands::NewObject nO(&session);
  session.execute(&nO);

  AnnotatorLib::Frame frame(1);

  AnnotatorLib::Commands::NewAnnotation nA(nO.getObject(), &frame, 10, 10, 5, 5,
                                           &session, false);
  session.execute(&nA);
  ASSERT_EQ(session.getAnnotations().size(), 1);
  ASSERT_EQ(nO.getObject()->getAnnotations().size(), 1);
  session.undo();
  ASSERT_EQ(session.getAnnotations().size(), 0);
  ASSERT_EQ(nO.getObject()->getAnnotations().size(), 0);
  session.redo();
  ASSERT_EQ(session.getAnnotations().size(), 1);
  ASSERT_EQ(nO.getObject()->getAnnotations().size(), 1);
}
