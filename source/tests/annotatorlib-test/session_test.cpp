
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
