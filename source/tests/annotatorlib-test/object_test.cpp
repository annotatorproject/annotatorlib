
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Class.h>
#include <AnnotatorLib/Project.h>
#include <gmock/gmock.h>
#include <string>
#include <algorithm>    // std::generate
#include <vector>       // std::vector
#include <cstdlib>      // std::rand, std::srand
#include <random>       // std::random_device

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
    shared_ptr<Annotation> annotation3 = Annotation::make_shared(make_shared<Frame>(3), obj, AnnotationType::RECTANGLE);
    shared_ptr<Annotation> annotation7 = Annotation::make_shared(make_shared<Frame>(7), obj, AnnotationType::RECTANGLE);

    obj->findClosestKeyFrames(make_shared<Frame>(1), prevA, nextA);
    ASSERT_TRUE(prevA.get() == nullptr);
    ASSERT_EQ(nextA, annotation3);

    obj->findClosestKeyFrames(make_shared<Frame>(5), prevA, nextA);
    ASSERT_EQ(prevA, annotation3);
    ASSERT_EQ(nextA, annotation7);

    obj->findClosestKeyFrames(make_shared<Frame>(9), prevA, nextA);
    ASSERT_EQ(prevA, annotation7);
    ASSERT_TRUE(nextA.get() == nullptr);

}
