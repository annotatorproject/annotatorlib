
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Session.h>
#include <gmock/gmock.h>
#include <string>

class session_test : public testing::Test {
 public:
};

TEST_F(session_test, getObject) {
  AnnotatorLib::Session session;
  AnnotatorLib::Object *o =
      new AnnotatorLib::Object(AnnotatorLib::Object::genId());
  o->setName("testname");
  session.addObject(o);

  AnnotatorLib::Object *o2 = session.getFirstObjectByName("testname");
  ASSERT_TRUE(o == o2);
  ASSERT_TRUE(o2->getName() == "testname");
}
