
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Class.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Project.h>
#include <gmock/gmock.h>
#include <algorithm>  // std::generate
#include <cstdlib>    // std::rand, std::srand
#include <random>     // std::random_device
#include <string>
#include <vector>  // std::vector

using namespace AnnotatorLib;
using namespace std;

class object_test : public testing::Test {
 public:
};

TEST_F(object_test, genId) {
  shared_ptr<Object> obj1 = make_shared<Object>();
  shared_ptr<Object> obj2 = make_shared<Object>();
  ASSERT_LT(obj1->getId(), obj2->getId());
}

TEST_F(object_test, findClosestKeyFrames) {
  shared_ptr<Annotation> prevA;
  shared_ptr<Annotation> nextA;

  shared_ptr<Object> obj = make_shared<Object>(std::make_shared<Class>("_"));
  shared_ptr<Annotation> annotation3 = Annotation::make_shared(
      make_shared<Frame>(3), obj, AnnotationType::RECTANGLE);
  shared_ptr<Annotation> annotation7 = Annotation::make_shared(
      make_shared<Frame>(7), obj, AnnotationType::RECTANGLE);
  shared_ptr<Annotation> annotation10 = Annotation::make_shared(
      make_shared<Frame>(10), obj, AnnotationType::RECTANGLE);
  shared_ptr<Annotation> annotation13 = Annotation::make_shared(
      make_shared<Frame>(13), obj, AnnotationType::RECTANGLE);

  obj->findClosestKeyFrames(make_shared<Frame>(1), prevA, nextA);
  ASSERT_TRUE(prevA.get() == nullptr);
  ASSERT_EQ(nextA, annotation3);

  obj->findClosestKeyFrames(make_shared<Frame>(5), prevA, nextA);
  ASSERT_EQ(prevA, annotation3);
  ASSERT_EQ(nextA, annotation7);

  obj->findClosestKeyFrames(make_shared<Frame>(15), prevA, nextA);
  ASSERT_EQ(prevA, annotation13);
  ASSERT_TRUE(nextA.get() == nullptr);

  obj->findClosestKeyFrames(make_shared<Frame>(3), prevA, nextA);
  ASSERT_EQ(prevA, nextA);
  ASSERT_EQ(prevA, annotation3);

  // find closest left
  ASSERT_EQ(annotation3->getFrame()->getFrameNumber(),
            obj->findClosestLeftKeyFrame(6)->getFrame()->getFrameNumber());
  ASSERT_EQ(annotation7->getFrame()->getFrameNumber(),
            obj->findClosestLeftKeyFrame(7)->getFrame()->getFrameNumber());
  ASSERT_EQ(annotation13->getFrame()->getFrameNumber(),
            obj->findClosestLeftKeyFrame(13)->getFrame()->getFrameNumber());
  ASSERT_EQ(annotation13->getFrame()->getFrameNumber(),
            obj->findClosestLeftKeyFrame(16)->getFrame()->getFrameNumber());
  ASSERT_EQ(annotation3->getFrame()->getFrameNumber(),
            obj->findClosestLeftKeyFrame(3)->getFrame()->getFrameNumber());
  ASSERT_EQ(annotation10->getFrame()->getFrameNumber(),
            obj->findClosestLeftKeyFrame(12)->getFrame()->getFrameNumber());
  ASSERT_EQ(nullptr, obj->findClosestLeftKeyFrame(1));

  // find closest right
  ASSERT_EQ(annotation3->getFrame()->getFrameNumber(),
            obj->findClosestRightKeyFrame(3)->getFrame()->getFrameNumber());
  ASSERT_EQ(annotation3->getFrame()->getFrameNumber(),
            obj->findClosestRightKeyFrame(1)->getFrame()->getFrameNumber());
  ASSERT_EQ(annotation13->getFrame()->getFrameNumber(),
            obj->findClosestRightKeyFrame(13)->getFrame()->getFrameNumber());
  ASSERT_EQ(annotation13->getFrame()->getFrameNumber(),
            obj->findClosestRightKeyFrame(12)->getFrame()->getFrameNumber());
  ASSERT_EQ(nullptr, obj->findClosestRightKeyFrame(20));
}
