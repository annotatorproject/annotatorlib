
#include <gmock/gmock.h>
#include <string>
#include <AnnotatorLib/Algo/InterpolateAnnotation.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Project.h>

class annotation_test : public testing::Test {
 public:
};

TEST_F(annotation_test, genId) {
  AnnotatorLib::Object obj;
  AnnotatorLib::Frame frame1(1);
  AnnotatorLib::Frame frame2(2);
  AnnotatorLib::Annotation annotation1(&frame1, &obj, AnnotatorLib::AnnotationType::RECTANGLE);
  AnnotatorLib::Annotation annotation2(&frame2, &obj, AnnotatorLib::AnnotationType::RECTANGLE);
  std::cout << "Annotation 1 id:" << annotation1.getId() << std::endl;
  std::cout << "Annotation 2 id:" << annotation2.getId() << std::endl;

  ASSERT_LT(annotation1.getId(), annotation2.getId());
}

TEST_F(annotation_test, previousAndNext) {

  //first object

  AnnotatorLib::Object obj;
  AnnotatorLib::Frame frame1(1);
  AnnotatorLib::Frame frame2(2);  
  AnnotatorLib::Annotation annotation2(&frame2, &obj, AnnotatorLib::AnnotationType::RECTANGLE);
  AnnotatorLib::Annotation annotation1(&frame1, &obj, AnnotatorLib::AnnotationType::RECTANGLE);

  ASSERT_EQ(annotation1.getNext(), &annotation2);
  ASSERT_EQ(annotation2.getPrevious(), &annotation1);

  ASSERT_EQ(annotation1.getPrevious(), nullptr);
  ASSERT_EQ(annotation2.getNext(), nullptr);

  //second object

  AnnotatorLib::Object obj2;
  AnnotatorLib::Frame frame5(5);
  AnnotatorLib::Annotation annotation5(&frame5, &obj2, AnnotatorLib::AnnotationType::RECTANGLE);

  AnnotatorLib::Frame frame10(10);
  AnnotatorLib::Annotation annotation10(&frame10, &obj2, AnnotatorLib::AnnotationType::RECTANGLE);

  ASSERT_EQ(annotation5.getNext(), &annotation10);
  ASSERT_EQ(annotation10.getPrevious(), &annotation5);
  ASSERT_EQ(annotation5.getPrevious(), nullptr);
  ASSERT_EQ(annotation10.getNext(), nullptr);

  AnnotatorLib::Frame frame15(15);
  AnnotatorLib::Annotation annotation15(&frame15, &obj2, AnnotatorLib::AnnotationType::RECTANGLE);

  ASSERT_EQ(annotation5.getNext(), &annotation10);
  ASSERT_EQ(annotation15.getPrevious(), &annotation10);
  ASSERT_EQ(annotation5.getPrevious(), nullptr);
  ASSERT_EQ(annotation15.getNext(), nullptr);

  obj2.removeAnnotation(&annotation15);
  ASSERT_EQ(annotation10.getNext(), nullptr);
  ASSERT_EQ(annotation15.getNext(), nullptr);
  ASSERT_EQ(annotation15.getPrevious(), nullptr);
}

TEST_F(annotation_test, interpolation) {
  AnnotatorLib::Object obj3;
  AnnotatorLib::Frame frame2(2);
  AnnotatorLib::Annotation annotation2(&frame2, &obj3, AnnotatorLib::AnnotationType::RECTANGLE);
  annotation2.setPosition(100, 200, 20, 40);

  AnnotatorLib::Frame frame4(4);
  AnnotatorLib::Annotation annotation4(&frame4, &obj3, AnnotatorLib::AnnotationType::RECTANGLE);
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

  delete annotation3;
}
