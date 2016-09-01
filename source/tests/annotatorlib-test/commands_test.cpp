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
}
