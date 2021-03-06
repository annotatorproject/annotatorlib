// Copyright 2016-2017 Annotator Team
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/CompressObject.h>
#include <AnnotatorLib/Commands/MergeObjects.h>
#include <AnnotatorLib/Commands/NewAnnotation.h>
#include <AnnotatorLib/Commands/NewAttribute.h>
#include <AnnotatorLib/Commands/RemoveAnnotation.h>
#include <AnnotatorLib/Commands/RemoveAnnotationRange.h>
#include <AnnotatorLib/Commands/RemoveAttribute.h>
#include <AnnotatorLib/Commands/RemoveObject.h>
#include <AnnotatorLib/Commands/UpdateAttribute.h>
#include <AnnotatorLib/Commands/UpdateObject.h>
#include <AnnotatorLib/Project.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

using std::shared_ptr;
using namespace AnnotatorLib;

class commands_test : public testing::Test {
 public:
};

TEST_F(commands_test, newAnnotation) {
  std::shared_ptr<Session> session = std::make_shared<Session>();
  ASSERT_EQ(session->getAnnotations().size(), (unsigned long)0);

  shared_ptr<Frame> frame = std::make_shared<Frame>(1);
  shared_ptr<Class> c = std::make_shared<Class>("car");

  Commands::NewAnnotation *nA =
      new Commands::NewAnnotation(1001, c, session, frame, 10, 10, 5, 5);

  session->execute(shared_ptr<Commands::Command>(nA));
  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  shared_ptr<Object> o = session->getObject(1001);
  ASSERT_EQ(o->getAnnotations().size(), 1ul);

  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 0ul);

  // call redo 2 times
  session->redo();
  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  session->redo();
  ASSERT_EQ(session->getAnnotations().size(), 1ul);

  // call undo 2 times
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 0ul);
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 0ul);

  for (unsigned long i = 0ul; i < 5; ++i) {
    session->execute(std::make_shared<Commands::NewAnnotation>(
        1001 + i, c, session, frame, 10, 10, 5, 5));
    ASSERT_EQ(session->getAnnotations().size(), i + 1);
    ASSERT_EQ(session->getObjects().size(), i + 1);
  }
  for (long i = 4ul; i >= 0; --i) {
    session->undo();
    ASSERT_EQ(session->getAnnotations().size(), (unsigned long)i);
    ASSERT_EQ(session->getObjects().size(), (unsigned long)i);
  }
}

TEST_F(commands_test, updateObject) {
  std::shared_ptr<Session> session = std::make_shared<Session>();
  auto frame = std::make_shared<Frame>(1);
  auto c = std::make_shared<Class>("car");

  Commands::NewAnnotation *nA =
      new Commands::NewAnnotation(1001, c, session, frame, 10, 10, 5, 5);

  session->execute(shared_ptr<Commands::Command>(nA));

  auto c_new = std::make_shared<Class>("person");

  Commands::UpdateObject *uO =
      new Commands::UpdateObject(session->getObject(1001), c_new);

  session->execute(shared_ptr<Commands::Command>(uO));
  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  ASSERT_EQ(session->getObjects().size(), 1ul);
  ASSERT_EQ(session->getObject(1001)->getClass()->getName(), "person");

  session->undo();
  ASSERT_EQ(session->getObject(1001)->getClass()->getName(), "car");
  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  ASSERT_EQ(session->getObjects().size(), 1ul);

  session->redo();
  ASSERT_EQ(session->getObject(1001)->getClass()->getName(), "person");
  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  ASSERT_EQ(session->getObjects().size(), 1ul);
}

TEST_F(commands_test, removeObject) {
  std::shared_ptr<Session> session = std::make_shared<Session>();

  auto frame = std::make_shared<Frame>(1);
  auto c = std::make_shared<Class>("car");

  Commands::NewAnnotation *nA =
      new Commands::NewAnnotation(1001, c, session, frame, 10, 10, 5, 5);

  session->execute(shared_ptr<Commands::Command>(nA));

  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  ASSERT_EQ(session->getObjects().size(), 1ul);

  session->execute(shared_ptr<Commands::Command>(
      new Commands::RemoveObject(session, session->getObject(1001))));
  ASSERT_EQ(session->getAnnotations().size(), 0ul);
  ASSERT_EQ(session->getObjects().size(), 0ul);

  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  ASSERT_EQ(session->getObjects().size(), 1ul);

  session->redo();
  ASSERT_EQ(session->getAnnotations().size(), 0ul);
  ASSERT_EQ(session->getObjects().size(), 0ul);
}

TEST_F(commands_test, removeAnnotation) {
  std::shared_ptr<Session> session = std::make_shared<Session>();
  ASSERT_EQ(session->getAnnotations().size(), 0ul);

  shared_ptr<Class> c = std::make_shared<Class>("car");
  shared_ptr<Object> o = std::make_shared<Object>(c);

  // create frame 2,4,6,8,10
  for (unsigned long i = 2; i < 11; i += 2) {
    session->execute(
        shared_ptr<Commands::NewAnnotation>(new Commands::NewAnnotation(
            session, o, std::make_shared<Frame>(i), 10, 10, 5, 5)));
  }

  ASSERT_EQ(session->getAnnotations().size(), 5ul);

  std::shared_ptr<Annotation> a2 =
      o->getAnnotation(session->getFrame((unsigned long)2));
  session->execute(shared_ptr<Commands::RemoveAnnotation>(
      new Commands::RemoveAnnotation(session, a2)));

  ASSERT_EQ(session->getAnnotations().size(), 4ul);
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 5ul);
  session->redo();
  ASSERT_EQ(session->getAnnotations().size(), 4ul);
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 5ul);

  // REMOVE RANGE
  session->execute(shared_ptr<Commands::RemoveAnnotationRange>(
      new Commands::RemoveAnnotationRange(session, o, 1ul, 3ul)));

  ASSERT_EQ(session->getAnnotations().size(), 4ul);
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 5ul);

  session->execute(shared_ptr<Commands::RemoveAnnotationRange>(
      new Commands::RemoveAnnotationRange(session, o, 1ul, 11ul)));

  ASSERT_EQ(session->getAnnotations().size(), 0ul);
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 5ul);

  session->execute(shared_ptr<Commands::RemoveAnnotationRange>(
      new Commands::RemoveAnnotationRange(session, o, 2ul, 4ul)));

  ASSERT_EQ(session->getAnnotations().size(), 3ul);
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 5ul);
}

TEST_F(commands_test, compressObject) {
  std::shared_ptr<Session> session = std::make_shared<Session>();
  shared_ptr<Object> obj = std::make_shared<Object>();

  for (unsigned long i = 0; i < 5; ++i) {
    shared_ptr<Frame> frame_i = std::make_shared<Frame>(i);
    session->addAnnotation(Annotation::make_shared(frame_i, obj));
    session->getAnnotation(frame_i, obj)->setPosition(i * 10, 40, 20, 20);
    ASSERT_EQ(session->getAnnotations().size(), i + 1);
    ASSERT_EQ(session->getFrames().size(), i + 1);
  }
  ASSERT_EQ(session->getFrames().size(), 5ul);
  ASSERT_EQ(obj->getAnnotations().size(), 5ul);

  Commands::CompressObject *cmd = new Commands::CompressObject(session, obj);
  session->execute(shared_ptr<Commands::Command>(cmd));

  ASSERT_EQ(obj->getAnnotations().size(), 2ul);

  session->undo();

  ASSERT_EQ(obj->getAnnotations().size(), 5ul);

  session->redo();

  ASSERT_EQ(obj->getAnnotations().size(), 2ul);
}

TEST_F(commands_test, mergeObjects) {
  std::shared_ptr<Session> session = std::make_shared<Session>();
  shared_ptr<Object> first = std::make_shared<Object>();

  for (unsigned long i = 0; i < 5; ++i) {
    shared_ptr<Frame> frame_i = std::make_shared<Frame>(i);
    session->addAnnotation(Annotation::make_shared(frame_i, first));
    session->getAnnotation(frame_i, first)->setPosition(i * 10, 40, 20, 20);
    ASSERT_EQ(session->getAnnotations().size(), i + 1);
    ASSERT_EQ(session->getFrames().size(), i + 1);
  }
  ASSERT_EQ(session->getFrames().size(), 5ul);
  ASSERT_EQ(first->getAnnotations().size(), 5ul);

  shared_ptr<Object> second = std::make_shared<Object>();

  for (unsigned long i = 5; i < 10; ++i) {
    shared_ptr<Frame> frame_i = std::make_shared<Frame>(i);
    session->addAnnotation(Annotation::make_shared(frame_i, second));
    session->getAnnotation(frame_i, second)->setPosition(i * 10, 40, 20, 20);
    ASSERT_EQ(session->getAnnotations().size(), i + 1);
    ASSERT_EQ(session->getFrames().size(), i + 1);
  }
  ASSERT_EQ(session->getFrames().size(), 10ul);
  ASSERT_EQ(second->getAnnotations().size(), 5ul);

  Commands::MergeObjects *cmd =
      new Commands::MergeObjects(session, first, second);
  session->execute(shared_ptr<Commands::Command>(cmd));

  ASSERT_EQ(first->getAnnotations().size(), 10ul);
  ASSERT_EQ(second->getAnnotations().size(), 0ul);
}

TEST_F(commands_test, newAttribute) {
  std::shared_ptr<Session> session = std::make_shared<Session>();
  ASSERT_EQ(session->getAnnotations().size(), (unsigned long)0);

  shared_ptr<Frame> frame = std::make_shared<Frame>(1);
  shared_ptr<Class> c = std::make_shared<Class>("car");

  Commands::NewAnnotation *nA =
      new Commands::NewAnnotation(1001, c, session, frame, 10, 10, 5, 5);

  session->execute(shared_ptr<Commands::Command>(nA));

  shared_ptr<Annotation> annotation = nA->getAnnotation();

  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  shared_ptr<Object> o = session->getObject(1001);
  ASSERT_EQ(o->getAnnotations().size(), 1ul);

  Commands::NewAttribute *nAttr =
      new Commands::NewAttribute(session, o, "string", "testattribute", "test");
  session->execute(shared_ptr<Commands::Command>(nAttr));
  ASSERT_EQ(annotation->getAttributes().size(), 1);

  std::shared_ptr<AnnotatorLib::Attribute> attribute_ =
      std::make_shared<AnnotatorLib::Attribute>("string", "scene");
  std::shared_ptr<AnnotatorLib::AttributeValue> av =
      AnnotatorLib::Attribute::createAttributeValue(
          AnnotatorLib::AttributeType::STRING, std::string("coast"));
  attribute_->setValue(av);

  Commands::NewAttribute *nfAttr =
      new Commands::NewAttribute(session, session->getFrame(1), attribute_);

  session->execute(shared_ptr<Commands::Command>(nfAttr));
  ASSERT_EQ(session->getFrame(1)->getAttributes().size(), 1);

  session->undo();
  ASSERT_EQ(session->getFrame(1)->getAttributes().size(), 0);

  delete nAttr;
  delete nfAttr;
}

TEST_F(commands_test, updateAttribute) {
  std::shared_ptr<Session> session = std::make_shared<Session>();
  ASSERT_EQ(session->getAnnotations().size(), (unsigned long)0);

  shared_ptr<Frame> frame = std::make_shared<Frame>(1);
  shared_ptr<Class> c = std::make_shared<Class>("car");

  Commands::NewAnnotation *nA =
      new Commands::NewAnnotation(1001, c, session, frame, 10, 10, 5, 5);

  session->execute(shared_ptr<Commands::Command>(nA));

  shared_ptr<Annotation> annotation = nA->getAnnotation();

  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  shared_ptr<Object> o = session->getObject(1001);
  ASSERT_EQ(o->getAnnotations().size(), 1ul);

  Commands::NewAttribute *nAttr =
      new Commands::NewAttribute(session, o, "string", "testattribute", "test");
  session->execute(shared_ptr<Commands::Command>(nAttr));
  ASSERT_EQ(annotation->getAttributes().size(), 1);

  Commands::NewAttribute *nAttr2 = new Commands::NewAttribute(
      session, o, "string", "testattribute2", "test2");
  session->execute(shared_ptr<Commands::Command>(nAttr2));
  ASSERT_EQ(annotation->getAttributes().size(), 2);

  Commands::UpdateAttribute *uAttr =
      new Commands::UpdateAttribute(annotation, "testattribute", "test1");
  session->execute(shared_ptr<Commands::Command>(uAttr));
  ASSERT_EQ(annotation->getAttributes().size(), 2);
  ASSERT_EQ(annotation->getAttributesWithoutDefaults().size(), 1);
  ASSERT_EQ(annotation->getAttribute("testattribute")->getValue()->getString(),
            "test1");
  ASSERT_EQ(o->getAttribute("testattribute")->getValue()->getString(), "test");
}

TEST_F(commands_test, removeAttribute) {
  std::shared_ptr<Session> session = std::make_shared<Session>();
  ASSERT_EQ(session->getAnnotations().size(), (unsigned long)0);

  shared_ptr<Frame> frame = std::make_shared<Frame>(1);
  shared_ptr<Class> c = std::make_shared<Class>("car");

  Commands::NewAnnotation *nA =
      new Commands::NewAnnotation(1001, c, session, frame, 10, 10, 5, 5);

  session->execute(shared_ptr<Commands::Command>(nA));

  shared_ptr<Annotation> annotation = nA->getAnnotation();

  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  shared_ptr<Object> o = session->getObject(1001);
  ASSERT_EQ(o->getAnnotations().size(), 1ul);

  std::shared_ptr<Commands::NewAttribute> nAttr =
      std::make_shared<Commands::NewAttribute>(session, o, "string",
                                               "testattribute", "test");
  session->execute(nAttr);
  std::shared_ptr<Attribute> attr = nAttr->getAttribute();
  ASSERT_EQ(annotation->getAttributes().size(), 1);

  std::shared_ptr<Commands::RemoveAttribute> rAttr =
      std::make_shared<Commands::RemoveAttribute>(session, o, "testattribute");
  session->execute(rAttr);

  ASSERT_EQ(annotation->getAttributes().size(), 0);
  session->undo();
  ASSERT_EQ(annotation->getAttributes().size(), 1);
  session->redo();
  ASSERT_EQ(annotation->getAttributes().size(), 0);
  session->undo();
  ASSERT_EQ(annotation->getAttributes().size(), 1);

  std::shared_ptr<Commands::RemoveAttribute> rAttr2 =
      std::make_shared<Commands::RemoveAttribute>(session, o, attr);
  session->execute(rAttr);

  ASSERT_EQ(annotation->getAttributes().size(), 0);
}
