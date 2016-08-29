
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Session.h>
#include <gmock/gmock.h>
#include <string>

class session_test : public testing::Test {
 public:
};

TEST_F(session_test, getObject) {
  AnnotatorLib::Session session;
  AnnotatorLib::Object *o = new AnnotatorLib::Object();
  AnnotatorLib::Frame *f = new AnnotatorLib::Frame(1);
  AnnotatorLib::Annotation *a = new AnnotatorLib::Annotation(f, o, AnnotatorLib::AnnotationType::RECTANGLE);
  o->addAnnotation(a);
  o->setName("testname");
  bool success = session.addObject(o);

  AnnotatorLib::Object *o2 = session.getFirstObjectByName("testname");
  ASSERT_TRUE(o == o2);
  ASSERT_TRUE(o2->getName() == "testname");
  ASSERT_TRUE(success);

  delete o;
  delete a;
  delete f;
}
