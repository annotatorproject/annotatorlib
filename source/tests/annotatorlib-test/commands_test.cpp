#include <gmock/gmock.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/NewAnnotation.h>
#include <AnnotatorLib/Project.h>
#include <string>

class commands_test : public testing::Test {
 public:
};

TEST_F(commands_test, newAnnotation) {
  AnnotatorLib::Session session;
  ASSERT_EQ(session.getAnnotations().size(), 0);

  AnnotatorLib::Frame frame(1);
  AnnotatorLib::Class c("car");

  AnnotatorLib::Commands::NewAnnotation nA(1001, &c, &frame, 10, 10, 5, 5,
                                           &session, false);
  session.execute(&nA);
  ASSERT_EQ(session.getAnnotations().size(), 1);

  session.undo();
  ASSERT_EQ(session.getAnnotations().size(), 0);

  session.redo();
  ASSERT_EQ(session.getAnnotations().size(), 1);
}
