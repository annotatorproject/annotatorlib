// Copyright 2016 Annotator Team
#include <AnnotatorLib/ImageSet/ImageFolder.h>
#include <AnnotatorLib/ImageSet/ImageSet.h>
#include <AnnotatorLib/ImageSet/ImageSetFactory.h>
#include <AnnotatorLib/ImageSet/Video.h>
#include <gmock/gmock.h>
#include <string>

class imageset_test : public testing::Test {
 public:
};

TEST_F(imageset_test, equals) {
  AnnotatorLib::Video *video =
      (AnnotatorLib::Video *)AnnotatorLib::ImageSetFactory::createImageSet(
          AnnotatorLib::ImageSetType::VIDEO, "video.mpg");
  AnnotatorLib::ImageSet *video2 =
      AnnotatorLib::ImageSetFactory::createImageSet(
          AnnotatorLib::ImageSetType::VIDEO, "video2.mpg");

  AnnotatorLib::ImageFolder *images = (AnnotatorLib::ImageFolder *)
      AnnotatorLib::ImageSetFactory::createImageSet(
          AnnotatorLib::ImageSetType::IMAGEFOLDER, "images/");
  AnnotatorLib::ImageSet *images2 =
      AnnotatorLib::ImageSetFactory::createImageSet(
          AnnotatorLib::ImageSetType::IMAGEFOLDER, "images2/");

  ASSERT_TRUE(video->equals(video));
  ASSERT_TRUE(!video->equals(video2));

  ASSERT_TRUE(images->equals(images));
  ASSERT_TRUE(!images->equals(images2));

  ASSERT_TRUE(!video->equals(images));

  delete video;
  delete video2;
  delete images;
  delete images2;
}
