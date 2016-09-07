#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/CompressObject.h>
#include <AnnotatorLib/Commands/NewAnnotation.h>
#include <AnnotatorLib/Commands/RemoveObject.h>
#include <AnnotatorLib/Commands/UpdateObject.h>
#include <AnnotatorLib/Project.h>
#include <gmock/gmock.h>
#include <string>
#include <memory>

using std::shared_ptr;
using namespace AnnotatorLib;

class commands_test : public testing::Test {
 public:
};

TEST_F(commands_test, newAnnotation) {
  Session* session = new Session();
  ASSERT_EQ(session->getAnnotations().size(), 0);

  shared_ptr<Frame> frame = std::make_shared<Frame>(1);
  shared_ptr<Class> c = std::make_shared<Class>("car");

  Commands::NewAnnotation* nA =
      new Commands::NewAnnotation(1001, c, session, frame, 10, 10, 5, 5);

  session->execute(shared_ptr<Commands::Command>(nA));
  ASSERT_EQ(session->getAnnotations().size(), 1);

  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 0);

  //call redo 2 times
  session->redo();
  ASSERT_EQ(session->getAnnotations().size(), 1);
  session->redo();
  ASSERT_EQ(session->getAnnotations().size(), 1);

  //call undo 2 times
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 0);
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 0);

  delete session;
}

TEST_F(commands_test, updateObject) {
  Session* session = new Session();
  auto frame = std::make_shared<Frame>(1);
  auto c = std::make_shared<Class>("car");

  Commands::NewAnnotation* nA =
      new Commands::NewAnnotation(1001, c, session, frame, 10, 10, 5, 5);

  session->execute(shared_ptr<Commands::Command>(nA));

  auto c_new = std::make_shared<Class>("person");

  Commands::UpdateObject* uO =
      new Commands::UpdateObject(session->getObject(1001), c_new);

  session->execute(shared_ptr<Commands::Command>(uO));
  ASSERT_EQ(session->getAnnotations().size(), 1);
  ASSERT_EQ(session->getObjects().size(), 1);
  ASSERT_EQ(session->getObject(1001)->getClass()->getName(), "person");

  session->undo();
  ASSERT_EQ(session->getObject(1001)->getClass()->getName(), "car");
  ASSERT_EQ(session->getAnnotations().size(), 1);
  ASSERT_EQ(session->getObjects().size(), 1);

  session->redo();
  ASSERT_EQ(session->getObject(1001)->getClass()->getName(), "person");
  ASSERT_EQ(session->getAnnotations().size(), 1);
  ASSERT_EQ(session->getObjects().size(), 1);

  delete session;
}

TEST_F(commands_test, removeObject) {
  Session* session = new Session();

  auto frame = std::make_shared<Frame>(1);
  auto c = std::make_shared<Class>("car");

  Commands::NewAnnotation* nA =
      new Commands::NewAnnotation(1001, c, session, frame, 10, 10, 5, 5);

  session->execute(shared_ptr<Commands::Command>(nA));

  Commands::RemoveObject* rO =
      new Commands::RemoveObject(session, session->getObject(1001));

  ASSERT_EQ(session->getAnnotations().size(), 1);
  ASSERT_EQ(session->getObjects().size(), 1);

  session->execute(shared_ptr<Commands::Command>(rO));
  ASSERT_EQ(session->getAnnotations().size(), 0);
  ASSERT_EQ(session->getObjects().size(), 0);

  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 1);
  ASSERT_EQ(session->getObjects().size(), 1);

  session->redo();
  ASSERT_EQ(session->getAnnotations().size(), 0);
  ASSERT_EQ(session->getObjects().size(), 0);

  delete session;
}

TEST_F(commands_test, compressObject) {
  Session* session = new Session();
  shared_ptr<Object> obj = std::make_shared<Object>();

  for (unsigned long i = 0; i < 5; ++i) {
    shared_ptr<Frame> frame_i = std::make_shared<Frame>(i);
    session->addAnnotation(Annotation::make_shared(frame_i, obj));
    session->getAnnotation(frame_i, obj)->setPosition(i * 10, 40, 20, 20);
    ASSERT_EQ(session->getAnnotations().size(), i + 1);
    ASSERT_EQ(session->getFrames().size(), i + 1);
  }  
  ASSERT_EQ(session->getFrames().size(), 5);
  ASSERT_EQ(obj->getAnnotations().size(), 5);

  Commands::CompressObject* cmd =
      new Commands::CompressObject(session, obj);
  session->execute(shared_ptr<Commands::Command>(cmd));

  ASSERT_EQ(obj->getAnnotations().size(), 2);

  session->undo();

  ASSERT_EQ(obj->getAnnotations().size(), 5);

  session->redo();

  ASSERT_EQ(obj->getAnnotations().size(), 2);

  delete session;
}
