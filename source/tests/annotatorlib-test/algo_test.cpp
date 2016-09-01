#include <AnnotatorLib/Algo/CompressObjectTrack.h>
#include <AnnotatorLib/Algo/InterpolateAnnotation.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>
#include <gmock/gmock.h>
#include <math.h>

class algo_test : public testing::Test {
 public:
};

TEST_F(algo_test, compressObjectTrack) {
  AnnotatorLib::Session session;
  AnnotatorLib::Object* obj = new AnnotatorLib::Object();

  for (unsigned long i = 0; i < 10; ++i) {
    AnnotatorLib::Frame* frame_i = new AnnotatorLib::Frame(i);
    AnnotatorLib::Annotation* a_i = new AnnotatorLib::Annotation(frame_i, obj);
    if (i < 5)
      a_i->setPosition(i * 10, 40, 20, 20);  // movement on a horiz. line
    else
      a_i->setPosition(i * 10, i * 10, 20, 20);  // movement on a diagonal line
    obj->addAnnotation(a_i);
  }
  session.addObject(obj);

  ASSERT_EQ(obj->getAnnotations().size(), 10);

  AnnotatorLib::Algo::CompressObjectTrack::compress(&session, obj);

  ASSERT_EQ(obj->getAnnotations().size(), 3);
}

TEST_F(algo_test, interpolation) {
  AnnotatorLib::Object obj3;
  AnnotatorLib::Frame frame2(2);
  AnnotatorLib::Annotation annotation2(&frame2, &obj3,
                                       AnnotatorLib::AnnotationType::RECTANGLE);
  annotation2.setPosition(100, 200, 20, 40);

  AnnotatorLib::Frame frame4(4);
  AnnotatorLib::Annotation annotation4(&frame4, &obj3,
                                       AnnotatorLib::AnnotationType::RECTANGLE);
  annotation4.setPosition(200, 140, 40, 30);

  AnnotatorLib::Frame frame3(3);
  AnnotatorLib::Annotation* annotation3 =
      AnnotatorLib::Algo::InterpolateAnnotation::getInterpolation(
          &frame3, &annotation2, &annotation4);

  ASSERT_EQ(annotation3->getFrame(), &frame3);
  ASSERT_EQ(annotation3->getX(), 150);
  ASSERT_EQ(annotation3->getY(), 170);
  ASSERT_EQ(annotation3->getHRadius(), 30 / 2.f);
  ASSERT_EQ(annotation3->getVRadius(), 35 / 2.f);
  ASSERT_EQ(annotation3->isInterpolated(), true);

  delete annotation3;
}

TEST_F(algo_test, interpolation2) {
  AnnotatorLib::Object obj3;
  AnnotatorLib::Frame frame2(2);
  AnnotatorLib::Annotation annotation2(&frame2, &obj3,
                                       AnnotatorLib::AnnotationType::RECTANGLE);
  annotation2.setPosition(100, -100, 20, 40);

  AnnotatorLib::Frame frame4(4);
  AnnotatorLib::Annotation annotation4(&frame4, &obj3,
                                       AnnotatorLib::AnnotationType::RECTANGLE);
  annotation4.setPosition(300, 100, 30, 20);

  AnnotatorLib::Frame frame3(3);
  AnnotatorLib::Annotation* annotation3 =
      AnnotatorLib::Algo::InterpolateAnnotation::getInterpolation(&frame3,
                                                                  &obj3, true);

  ASSERT_EQ(annotation3->getFrame(), &frame3);
  ASSERT_EQ(annotation3->getX(), 200);
  ASSERT_EQ(annotation3->getY(), 0);
  ASSERT_EQ(annotation3->getHRadius(), 25 / 2.f);
  ASSERT_EQ(annotation3->getVRadius(), 30 / 2.f);
  ASSERT_EQ(annotation3->isInterpolated(), true);

  delete annotation3;
}
