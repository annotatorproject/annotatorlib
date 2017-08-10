// Copyright 2016 Annotator Team
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Session.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

using namespace AnnotatorLib;
using std::shared_ptr;

class session_test : public testing::Test {
 public:
};

TEST_F(session_test, getObject) {
  Session session;
  shared_ptr<Object> o = std::make_shared<Object>();
  shared_ptr<Frame> f = std::make_shared<Frame>(1);
  shared_ptr<Annotation> a =
      Annotation::make_shared(f, o, AnnotationType::RECTANGLE);
  o->setName("testname");
  bool success = session.addAnnotation(a, true);

  shared_ptr<Object> o2 = session.getObject(o->getId());
  ASSERT_TRUE(o == o2);
  ASSERT_TRUE(o2->getName() == "testname");
  ASSERT_TRUE(success);
}

TEST_F(session_test, getFrames) {
  std::shared_ptr<Session> session = std::make_shared<Session>();
  shared_ptr<Object> o = std::make_shared<Object>();
  for (unsigned long i = 0; i < 5; ++i) {
    shared_ptr<Frame> frame_i = std::make_shared<Frame>(i);
    session->addAnnotation(Annotation::make_shared(frame_i, o));
    session->getAnnotation(frame_i, o)->setPosition(i * 10, 40, 20, 20);
    ASSERT_EQ(session->getAnnotations().size(), i + 1);
    ASSERT_EQ(session->getFrames().size(), i + 1);
  }
  ASSERT_EQ(session->getFramesRange(1, 3).size(), 3);
  ASSERT_EQ(session->getFramesRange(4, 10).size(), 1);
}
