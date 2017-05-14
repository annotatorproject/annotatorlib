// Copyright 2016 Annotator Team
#include <../../storages/sqlite/SQLiteStorage.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Session.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

using namespace AnnotatorLib;
using std::shared_ptr;

class storage_sqlite_test : public testing::Test {
 public:
};

TEST_F(storage_sqlite_test, createTables) {
  SQLiteStorage storage;
  storage.setPath("annotator.db");
  ASSERT_TRUE(storage.open());
}

TEST_F(storage_sqlite_test, objects) {
  SQLiteStorage storage;
  storage.setPath("annotator.db");
  ASSERT_TRUE(storage.open());
  auto c = std::make_shared<Class>("testclass");

  storage.addClass(c);
  storage.removeClass(c.get());

  shared_ptr<Object> o = std::make_shared<Object>();
  o->setClass(c);
  o->setName("testobject");
  storage.addObject(o);

  shared_ptr<Object> o2 = storage.getObject(o->getId());
  ASSERT_TRUE(o == o2);
  ASSERT_TRUE(o2->getName() == "testobject");

  SQLiteStorage storage2;
  storage2.setPath("annotator.db");
  ASSERT_TRUE(storage2.open());
  shared_ptr<Object> o3 = storage2.getObject(o->getId());
  ASSERT_TRUE(o3->getName() == "testobject");
}

TEST_F(storage_sqlite_test, annotations) {
  SQLiteStorage storage;
  storage.setPath("annotator.db");
  ASSERT_TRUE(storage.open());
  auto c = std::make_shared<Class>("testclass");

  storage.addClass(c);
  storage.removeClass(c.get());

  shared_ptr<Object> o = std::make_shared<Object>();
  o->setClass(c);
  o->setName("testobject");
  storage.addObject(o);

  shared_ptr<Object> o2 = storage.getObject(o->getId());
  ASSERT_TRUE(o == o2);
  ASSERT_TRUE(o2->getName() == "testobject");

  shared_ptr<Frame> f = std::make_shared<Frame>(1);
  shared_ptr<Annotation> a =
      Annotation::make_shared(f, o, AnnotationType::RECTANGLE);
  a->setPosition(0, 0, 1, 1);
  ASSERT_TRUE(storage.addAnnotation(a, true));

  SQLiteStorage storage2;
  storage2.setPath("annotator.db");
  ASSERT_TRUE(storage2.open());
  shared_ptr<Object> o3 = storage2.getObject(o->getId());
  ASSERT_TRUE(o3->getName() == "testobject");

  shared_ptr<Annotation> a2 = storage2.getAnnotation(a->getId());
  ASSERT_TRUE(storage2.getAnnotations().size() > 0);
  ASSERT_TRUE(a2->getObject()->getName() == "testobject");
  ASSERT_TRUE(storage2.getFrames().size() == 1);
}
