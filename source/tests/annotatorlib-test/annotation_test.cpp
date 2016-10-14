
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

class annotation_test : public testing::Test {
 public:
};

TEST_F(annotation_test, genId) {

  shared_ptr<Object> obj = make_shared<Object>();
  shared_ptr<Annotation> annotation1 = Annotation::make_shared(make_shared<Frame>(1), obj, AnnotationType::RECTANGLE);
  shared_ptr<Annotation> annotation2 = Annotation::make_shared(make_shared<Frame>(2), obj, AnnotationType::RECTANGLE);

  ASSERT_LT(annotation1->getId(), annotation2->getId());
}

TEST_F(annotation_test, previousAndNext) {

  Session session;

  // first object
  shared_ptr<Object> obj = make_shared<Object>(std::make_shared<Class>("dog"));
  shared_ptr<Annotation> annotation1 = Annotation::make_shared(make_shared<Frame>(1), obj, AnnotationType::RECTANGLE);
  shared_ptr<Annotation> annotation2 = Annotation::make_shared(make_shared<Frame>(2), obj, AnnotationType::RECTANGLE);

  ASSERT_EQ(annotation1->getNext().get(), annotation2.get());
  ASSERT_EQ(annotation2->getPrevious(), annotation1);

  ASSERT_EQ(annotation1->getPrevious().get(), nullptr);
  ASSERT_EQ(annotation2->getNext().get(), nullptr);

  // second object
  shared_ptr<Object> obj2 = make_shared<Object>();
  shared_ptr<Annotation> annotation5 = Annotation::make_shared(make_shared<Frame>(5), obj2, AnnotationType::RECTANGLE);
  shared_ptr<Annotation> annotation10 = Annotation::make_shared(make_shared<Frame>(10), obj2, AnnotationType::RECTANGLE);

  ASSERT_EQ(annotation5->getNext(), annotation10);
  ASSERT_EQ(annotation10->getPrevious(), annotation5);
  ASSERT_EQ(annotation5->getPrevious(), nullptr);
  ASSERT_EQ(annotation10->getNext(), nullptr);

  shared_ptr<Annotation> annotation15 = Annotation::make_shared(make_shared<Frame>(15), obj2, AnnotationType::RECTANGLE);

  ASSERT_EQ(annotation5->getNext(), annotation10);
  ASSERT_EQ(annotation15->getPrevious(), annotation10);
  ASSERT_EQ(annotation5->getPrevious().get(), nullptr);
  ASSERT_EQ(annotation15->getNext().get(), nullptr);

  obj2->removeAnnotation(annotation15);
  ASSERT_EQ(annotation10->getNext().get(), nullptr);
  ASSERT_EQ(annotation15->getNext().get(), nullptr);
  ASSERT_EQ(annotation15->getPrevious().get(), nullptr);
}

TEST_F(annotation_test, checkOrder) {

  shared_ptr<Object> obj = make_shared<Object>();

  std::vector<unsigned long> unique_nmbs (200);
  std::vector<shared_ptr<Annotation>> unique_annotations;
  random_device rnd_device;
  mt19937 mersenne_engine(rnd_device());
  uniform_int_distribution<int> dist(0, 1000);
  auto gen = std::bind(dist, mersenne_engine);
  std::generate(unique_nmbs.begin(), unique_nmbs.end(), gen);
  sort( unique_nmbs.begin(), unique_nmbs.end() );
  unique_nmbs.erase( unique( unique_nmbs.begin(), unique_nmbs.end() ), unique_nmbs.end() );
  unique_nmbs.shrink_to_fit();
  for (unsigned long nmb : unique_nmbs) {
    shared_ptr<Annotation> a = Annotation::make_shared(make_shared<Frame>(nmb), obj);
    unique_annotations.push_back(a);
  }
  shared_ptr<Annotation> prev;
  for (auto& pair : obj->getAnnotations()) {
      shared_ptr<Annotation> a = pair.second.lock();
      if (a != obj->getFirstAnnotation()) {
        ASSERT_LT(*prev.get(), *a.get());
        ASSERT_LT(*prev->getFrame().get(), *a->getFrame().get());
        ASSERT_LT(prev->getFrame()->getId(), a->getFrame()->getId());
        ASSERT_EQ(a->getPrevious(), prev);
        ASSERT_EQ(prev->getNext(), a);
      }
      prev = a;
  }
}

TEST_F(annotation_test, annotationLifeTime) {

  shared_ptr<Object> obj = make_shared<Object>();
  shared_ptr<Frame> frame1 = make_shared<Frame>(1);
  shared_ptr<Frame> frame2 = make_shared<Frame>(2);
  ASSERT_EQ(obj->getAnnotations().size(), (unsigned long) 0);
  ASSERT_EQ(frame1->getAnnotations().size(),(unsigned long) 0);
  shared_ptr<Annotation> annotation1 = Annotation::make_shared(frame1, obj, AnnotationType::RECTANGLE);
  annotation1->setHRadius(10.f);
  ASSERT_EQ(obj->getAnnotations().size(), (unsigned long) 1);
  ASSERT_EQ(frame1->getAnnotations().size(), (unsigned long) 1);
  ASSERT_EQ(frame2->getAnnotations().size(), (unsigned long) 0);
  if (true) {
    shared_ptr<Annotation> annotation2 = Annotation::make_shared(frame2, obj, AnnotationType::RECTANGLE);
    ASSERT_EQ(obj->getAnnotations().size(), (unsigned long) 2);
    ASSERT_EQ(frame1->getAnnotations().size(), (unsigned long) 1);
    ASSERT_EQ(frame2->getAnnotations().size(), (unsigned long) 1);
    annotation2.reset();
  }
  ASSERT_EQ(obj->getAnnotations().size(), (unsigned long) 1);     //was annotation2 automatically unregistered?
  ASSERT_EQ(frame1->getAnnotations().size(), (unsigned long) 1);
  ASSERT_EQ(frame2->getAnnotations().size(), (unsigned long) 0);  //was annotation2 automatically unregistered?
}

TEST_F(annotation_test, classTest) {

  // first object
  shared_ptr<Object> obj = make_shared<Object>(std::make_shared<Class>("dog"));
  shared_ptr<Annotation> annotation1 = Annotation::make_shared(make_shared<Frame>(1), obj, AnnotationType::RECTANGLE);

  ASSERT_EQ(obj->getClass()->getName(), "dog");
  ASSERT_EQ(annotation1->getObject()->getClass()->getName(), "dog");

  obj->setClass(std::make_shared<Class>("cat"));

  ASSERT_EQ(obj->getClass()->getName(), "cat");
  ASSERT_EQ(annotation1->getObject()->getClass()->getName(), "cat");

}
