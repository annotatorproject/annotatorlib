// Copyright 2016 Annotator Team
#include <AnnotatorLib/Attribute.h>
#include <AnnotatorLib/Project.h>
#include <gmock/gmock.h>
#include <math.h>
#include <string>

class attribute_test : public testing::Test {
 public:
};

TEST_F(attribute_test, testString) {
  std::string s = "Hello";
  AnnotatorLib::AttributeValue av(s);

  ASSERT_FALSE(av.getString() == "");
  ASSERT_EQ(av.getString(), "Hello");

  AnnotatorLib::AttributeValue av2("World");
  ASSERT_FALSE(av2.getString() == "Hello");
  ASSERT_EQ(av2.getString(), "World");
  int exceptions = 0;
  try {
    av2.getInteger();
  } catch (...) {
    exceptions++;
  }
  try {
    av2.getFloat();
  } catch (...) {
    exceptions++;
  }
  try {
    av2.getBoolean();
  } catch (...) {
    exceptions++;
  }
  ASSERT_EQ(exceptions, 3);
}

TEST_F(attribute_test, testInteger) {
  AnnotatorLib::AttributeValue av(1337l);

  ASSERT_EQ(av.getInteger(), 1337);

  AnnotatorLib::AttributeValue av2(42);

  ASSERT_EQ(av2.getInteger(), 42);
}

TEST_F(attribute_test, testFloat) {
  AnnotatorLib::AttributeValue av(3.14);
  ASSERT_EQ(av.getFloat(), 3.14);

  AnnotatorLib::AttributeValue av2(3.14f);
  ASSERT_LT(std::abs(av2.getFloat() - av.getFloat()), 0.001);
}

TEST_F(attribute_test, testBoolean) {
  AnnotatorLib::AttributeValue av(false);

  ASSERT_FALSE(av.getBoolean() == true);
  ASSERT_TRUE(av.getBoolean() == false);
}

TEST_F(attribute_test, testEquals) {
  AnnotatorLib::Attribute a(AnnotatorLib::Attribute::genId(),
                            AnnotatorLib::AttributeType::BOOLEAN, "light");
  AnnotatorLib::Attribute b(AnnotatorLib::Attribute::genId(),
                            AnnotatorLib::AttributeType::BOOLEAN, "light");
  AnnotatorLib::Attribute c(AnnotatorLib::Attribute::genId(),
                            AnnotatorLib::AttributeType::INTEGER, "doors");
  AnnotatorLib::Attribute d(AnnotatorLib::Attribute::genId(),
                            AnnotatorLib::AttributeType::INTEGER, "light");

  ASSERT_TRUE(a.equals(&a));
  ASSERT_TRUE(a.equals(&b));
  ASSERT_TRUE(!a.equals(&c));
  ASSERT_TRUE(!a.equals(&d));
}
