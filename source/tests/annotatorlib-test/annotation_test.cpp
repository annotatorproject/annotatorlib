
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Project.h>
#include <gmock/gmock.h>
#include <string>

using namespace AnnotatorLib;
using namespace std;

class annotation_test : public testing::Test {
 public:
};

TEST_F(annotation_test, genId) {

  shared_ptr<Object> obj = make_shared<Object>();
  shared_ptr<Annotation> annotation1 = Annotation::make_shared(make_shared<Frame>(1), obj, AnnotationType::RECTANGLE);
  shared_ptr<Annotation> annotation2 = Annotation::make_shared(make_shared<Frame>(2), obj, AnnotationType::RECTANGLE);

  cout << "shared_ptr<Annotation> 1 id:" << annotation1->getId() << endl;
  cout << "shared_ptr<Annotation> 2 id:" << annotation2->getId() << endl;

  ASSERT_LT(annotation1->getId(), annotation2->getId());
}

TEST_F(annotation_test, previousAndNext) {

  Session session;

  // first object
  shared_ptr<Object> obj = make_shared<Object>();
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

TEST_F(annotation_test, annotationLifeTime) {

  shared_ptr<Object> obj = make_shared<Object>();
  shared_ptr<Frame> frame1 = make_shared<Frame>(1);
  shared_ptr<Frame> frame2 = make_shared<Frame>(2);
  ASSERT_EQ(obj->getAnnotations().size(), 0);
  ASSERT_EQ(frame1->getAnnotations().size(), 0);
  shared_ptr<Annotation> annotation1 = Annotation::make_shared(frame1, obj, AnnotationType::RECTANGLE);
  ASSERT_EQ(obj->getAnnotations().size(), 1);
  ASSERT_EQ(frame1->getAnnotations().size(), 1);
  ASSERT_EQ(frame2->getAnnotations().size(), 0);
  if (true) {
    shared_ptr<Annotation> annotation2 = Annotation::make_shared(frame2, obj, AnnotationType::RECTANGLE);
    ASSERT_EQ(obj->getAnnotations().size(), 2);
    ASSERT_EQ(frame1->getAnnotations().size(), 1);
    ASSERT_EQ(frame2->getAnnotations().size(), 1);
    annotation2.reset();
  }
  ASSERT_EQ(obj->getAnnotations().size(), 1);
  ASSERT_EQ(frame1->getAnnotations().size(), 1);
  ASSERT_EQ(frame2->getAnnotations().size(), 0);
}
