// Copyright 2016 Annotator Team
#ifndef NEWANNOTATION_H
#define NEWANNOTATION_H

#include <AnnotatorLib/Commands/Command.h>
#include <memory>
#include <string>

using std::shared_ptr;

namespace AnnotatorLib {

class Object;
class Class;
class Session;
class Annotation;
class Frame;

namespace Commands {

class ANNOTATORLIB_API NewAnnotation : public Command {
 public:
  NewAnnotation() = delete;

  NewAnnotation(const unsigned long newObjectId,
                const shared_ptr<Class> newObjectClass,
                std::shared_ptr<Session> session, shared_ptr<Frame> frame,
                float x, float y, float width, float height,
                float confidence = 1.0, bool objectActive = true);

  NewAnnotation(std::shared_ptr<Session> session, shared_ptr<Object> object_,
                shared_ptr<Frame> frame_, float x, float y, float width,
                float height, float confidence = 1.0);

  NewAnnotation(const NewAnnotation &other) = delete;

  ~NewAnnotation() {}

  virtual bool execute(Session *informSession = 0) override;

  virtual bool undo(Session *informSession = 0) override;

  shared_ptr<Annotation> getAnnotation();
  bool newObjectCreated() { return createdNewObject; }

 protected:
  float x, y, width, height;
  float confidence;
  shared_ptr<Session> session;
  shared_ptr<Object> object;
  shared_ptr<Frame> frame;
  const unsigned long newObjectId;
  const shared_ptr<Class> newObjectClass;
  shared_ptr<Annotation> annotation_;
  const bool createNewObject;
  bool objectActive = true;
  bool createdNewObject = false;
};
}
}
#endif  // NEWANNOTATION_H
