#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Class.h>
#include <AnnotatorLib/Project.h>
#include <AnnotatorLib/Session.h>
#include <AnnotatorLib/Algo/SmoothAnnotation.h>
#include <gmock/gmock.h>
#include <string>

using namespace AnnotatorLib;
using namespace std;

class algo_smooth_test : public testing::Test {
 public:
};

TEST_F(algo_smooth_test, interpolate) {
    ASSERT_EQ(5, AnnotatorLib::Algo::SmoothAnnotation::interpolate(0, 10, 1, 1));
    ASSERT_EQ(5, AnnotatorLib::Algo::SmoothAnnotation::interpolate(5, 5, 1, 1));
    ASSERT_EQ(2.5, AnnotatorLib::Algo::SmoothAnnotation::interpolate(0, 10, 0.5, 1));
    ASSERT_EQ(2.5, AnnotatorLib::Algo::SmoothAnnotation::interpolate(0, 10, 1, 2));
    ASSERT_EQ(0, AnnotatorLib::Algo::SmoothAnnotation::interpolate(0, 10, 0, 2));
}

TEST_F(algo_smooth_test, getInterpolation) {

  shared_ptr<Session> session = shared_ptr<Session>(new Session());
  shared_ptr<Frame> frame1 = make_shared<Frame>(1);
  shared_ptr<Frame> frame2 = make_shared<Frame>(2);
  shared_ptr<Frame> frame3 = make_shared<Frame>(3);
  session->addFrame(frame1);
  session->addFrame(frame2);
  session->addFrame(frame3);
  // first object
  shared_ptr<Object> obj = make_shared<Object>(std::make_shared<Class>("unspecified"));
  session->addObject(obj);
  shared_ptr<Annotation> annotation1 = Annotation::make_shared(frame1, obj, AnnotationType::RECTANGLE);
  annotation1->setX(0);
  annotation1->setY(0);
  annotation1->setWidth(100);
  annotation1->setHeight(100);
  annotation1->setConfidenceScore(1);
  session->addAnnotation(annotation1);
  shared_ptr<Annotation> annotation3 = Annotation::make_shared(frame3, obj, AnnotationType::RECTANGLE);
  annotation3->setX(100);
  annotation3->setY(100);
  annotation3->setWidth(200);
  annotation3->setHeight(200);
  annotation3->setConfidenceScore(0);
  session->addAnnotation(annotation3);

  shared_ptr<Annotation> annotation = AnnotatorLib::Algo::SmoothAnnotation::getInterpolation(session, frame2, obj, 1);
  // ASSERT_EQ(annotation->getX(), 25);
  // ASSERT_EQ(annotation->getY(), 25);
  // ASSERT_EQ(annotation->getWidth(), 125);
  // ASSERT_EQ(annotation->getHeight(), 125);
}
