#include <AnnotatorLib/Algo/AdjustAnnotation.h>
#include <AnnotatorLib/Algo/InterpolateAnnotation.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Class.h>
#include <AnnotatorLib/Commands/AdjustNeighbors.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Project.h>
#include <AnnotatorLib/Session.h>

#include <gmock/gmock.h>
#include <string>

using namespace AnnotatorLib;
using namespace std;

class command_adjustneighbors : public testing::Test {
 public:
};

TEST_F(command_adjustneighbors, execute) {
  shared_ptr<Session> session = shared_ptr<Session>(new Session());
  shared_ptr<Frame> frame1 = make_shared<Frame>(1);
  shared_ptr<Frame> frame2 = make_shared<Frame>(2);
  shared_ptr<Frame> frame3 = make_shared<Frame>(3);
  session->addFrame(frame1);
  session->addFrame(frame2);
  session->addFrame(frame3);
  // first object
  shared_ptr<Object> obj =
      make_shared<Object>(std::make_shared<Class>("unspecified"));
  session->addObject(obj);
  shared_ptr<Annotation> annotation1 =
      Annotation::make_shared(frame1, obj, AnnotationType::RECTANGLE);
  annotation1->setX(0);
  annotation1->setY(0);
  annotation1->setWidth(100);
  annotation1->setHeight(100);
  annotation1->setConfidenceScore(1);
  session->addAnnotation(annotation1);
  shared_ptr<Annotation> annotation3 =
      Annotation::make_shared(frame3, obj, AnnotationType::RECTANGLE);
  annotation3->setX(100);
  annotation3->setY(100);
  annotation3->setWidth(200);
  annotation3->setHeight(200);
  annotation3->setConfidenceScore(0);
  session->addAnnotation(annotation3);

  shared_ptr<Annotation> annotation2 =
      AnnotatorLib::Algo::InterpolateAnnotation::getInterpolation(session,
                                                                  frame2, obj);
  float oldX = annotation2->getX();
  float oldY = annotation2->getY();

  shared_ptr<AnnotatorLib::Commands::AdjustNeighbors> anCommand =
      std::make_shared<AnnotatorLib::Commands::AdjustNeighbors>(session,
                                                                annotation3, 1);
  anCommand->execute();
  annotation2 = AnnotatorLib::Algo::InterpolateAnnotation::getInterpolation(
      session, frame2, obj);
  ASSERT_NE(annotation2->getX(), oldX);
  ASSERT_NE(annotation2->getY(), oldY);
}
