
#include <gmock/gmock.h>
#include <string>
#include <AnnotatorLib/Algo/InterpolateAnnotation.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Project.h>

class annotation_test : public testing::Test {
 public:
};

TEST_F(annotation_test, genId) {
  AnnotatorLib::Annotation annotation1(nullptr, nullptr, AnnotatorLib::AnnotationType::RECTANGLE);
  AnnotatorLib::Annotation annotation2(nullptr, nullptr, AnnotatorLib::AnnotationType::RECTANGLE);
  std::cout << "Annotation 1 id:" << annotation1.getId() << std::endl;
  std::cout << "Annotation 2 id:" << annotation2.getId() << std::endl;

  ASSERT_LT(annotation1.getId(), annotation2.getId());
}

TEST_F(annotation_test, previousAndNext) {
  AnnotatorLib::Annotation annotation1(nullptr, nullptr, AnnotatorLib::AnnotationType::RECTANGLE);
  AnnotatorLib::Annotation annotation2(nullptr, nullptr, AnnotatorLib::AnnotationType::RECTANGLE);
  annotation1.setNext(&annotation2);
  annotation2.setPrevious(&annotation1);

  ASSERT_EQ(annotation1.getNext(), &annotation2);
  ASSERT_EQ(annotation2.getPrevious(), &annotation1);

  ASSERT_EQ(annotation1.getPrevious(), nullptr);
  ASSERT_EQ(annotation2.getNext(), nullptr);
}

TEST_F(annotation_test, interpolation) {
  AnnotatorLib::Frame frame5(5);
  AnnotatorLib::Annotation annotation5(&frame5, nullptr, AnnotatorLib::AnnotationType::RECTANGLE);
  annotation5.setPosition(100, 200, 20, 40);

  AnnotatorLib::Frame frame15(15);
  AnnotatorLib::Annotation annotation15(&frame15, nullptr, AnnotatorLib::AnnotationType::RECTANGLE);
  annotation15.setPosition(200, 140, 40, 30);

  AnnotatorLib::Frame frame10(10);
  AnnotatorLib::Annotation* annotation10 =
      AnnotatorLib::Algo::InterpolateAnnotation::getInterpolation(
          &frame10, &annotation5, &annotation15);

  ASSERT_EQ(annotation10->getFrame(), &frame10);
  ASSERT_EQ(annotation10->getX(), 150);
  ASSERT_EQ(annotation10->getY(), 170);
  ASSERT_EQ(annotation10->getHRadius(), 30);
  ASSERT_EQ(annotation10->getVRadius(), 35);

  delete annotation10;
}
