// Copyright 2016-2017 Annotator Team
#include <AnnotatorLib/ImageSet/AbstractImageSet.h>
#include <AnnotatorLib/ImageSet/ImageFolder.h>
#include <AnnotatorLib/ImageSet/ImageSetFactory.h>
#include <gmock/gmock.h>
#include <string>

class imageset_test : public testing::Test {
 public:
};

TEST_F(imageset_test, equals) {
  std::shared_ptr<AnnotatorLib::ImageSet::AbstractImageSet> video =
      AnnotatorLib::ImageSet::ImageSetFactory::instance()->createImageSet(
          "video", "video.mpg");
  std::shared_ptr<AnnotatorLib::ImageSet::AbstractImageSet> video2 =
      AnnotatorLib::ImageSet::ImageSetFactory::instance()->createImageSet(
          "video", "video2.mpg");

  std::shared_ptr<AnnotatorLib::ImageSet::AbstractImageSet> images =
      AnnotatorLib::ImageSet::ImageSetFactory::instance()->createImageSet(
          "images", "images/");
  std::shared_ptr<AnnotatorLib::ImageSet::AbstractImageSet> images2 =
      AnnotatorLib::ImageSet::ImageSetFactory::instance()->createImageSet(
          "images", "images2/");

  ASSERT_TRUE(video->equals(video));
  ASSERT_TRUE(!video->equals(video2));

  ASSERT_TRUE(images->equals(images));
  ASSERT_TRUE(!images->equals(images2));

  ASSERT_TRUE(!video->equals(images));
}
