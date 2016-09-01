#include <gmock/gmock.h>
#include <AnnotatorLib/Session.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Algo/CompressObjectTrack.h>

class algo_test : public testing::Test {
 public:
};

TEST_F(algo_test, compressObjectTrack) {
  AnnotatorLib::Session session;
  AnnotatorLib::Object* obj = new AnnotatorLib::Object();

  for(unsigned long i = 0; i < 10; ++i) {
    AnnotatorLib::Frame* frame_i = new AnnotatorLib::Frame(i);
    AnnotatorLib::Annotation* a_i = new AnnotatorLib::Annotation(frame_i, obj);
    a_i->setPosition(10, 10, 20, 20);
    obj->addAnnotation(a_i);
  }
  session.addObject(obj);

  ASSERT_EQ(obj->getAnnotations().size(), 10);

  AnnotatorLib::Algo::CompressObjectTrack::compress(&session, obj);

  ASSERT_EQ(obj->getAnnotations().size(), 2);

}
