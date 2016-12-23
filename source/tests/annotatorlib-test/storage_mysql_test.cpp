// Copyright 2016 Annotator Team
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Session.h>
#include <AnnotatorLib/Storage/MySQLStorage.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

using namespace AnnotatorLib;
using std::shared_ptr;

class storage_mysql_test : public testing::Test {
 public:
};

TEST_F(storage_mysql_test, createTables) {
    AnnotatorLib::Storage::MySQLStorage storage;
    storage.setPath("host=localhost;user=annotator;password=annotator;db=annotatortestdb;auto-reconnect=true");
    ASSERT_TRUE(storage.open());
    auto c = std::make_shared<Class>("car");

    storage.addClass(c);
    storage.removeClass(c.get());

    shared_ptr<Object> o = std::make_shared<Object>();
    shared_ptr<Frame> f = std::make_shared<Frame>(1);
    shared_ptr<Annotation> a =
        Annotation::make_shared(f, o, AnnotationType::RECTANGLE);
    o->setName("testname");
    bool success = storage.addAnnotation(a, true);

    shared_ptr<Object> o2 = storage.getObject(o->getId());
    ASSERT_TRUE(o == o2);
    ASSERT_TRUE(o2->getName() == "testname");
    ASSERT_TRUE(success);
}
