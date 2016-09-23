#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/RemoveAnnotation.h>
#include <AnnotatorLib/Commands/RemoveAnnotationRange.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::RemoveAnnotationRange::RemoveAnnotationRange(
    std::shared_ptr<AnnotatorLib::Session> s,
    shared_ptr<AnnotatorLib::Object> o, shared_ptr<AnnotatorLib::Frame> f1,
    shared_ptr<AnnotatorLib::Frame> f2) {
  this->session = s;
  this->object = o;
  this->frame1 = f1;
  this->frame2 = f2;
}

bool AnnotatorLib::Commands::RemoveAnnotationRange::execute() {
  removeCommands.clear();
  for (unsigned long i = frame1->getFrameNumber();
       i <= frame2->getFrameNumber(); ++i) {
    std::shared_ptr<AnnotatorLib::Frame> frame = session->getFrame(i);
    if (frame) {
      std::shared_ptr<AnnotatorLib::Annotation> annotation = object->getAnnotation(frame);
      if (annotation) {
        RemoveAnnotation command(session, annotation);
        removeCommands.push_back(command);
      }
    }
  }
}

bool AnnotatorLib::Commands::RemoveAnnotationRange::undo() {
  bool success = true;
  for (RemoveAnnotation c : removeCommands) {
    success = success && c.undo();
  }
  return success;
}

shared_ptr<AnnotatorLib::Object>
AnnotatorLib::Commands::RemoveAnnotationRange::getObject() {
  return object;
}

shared_ptr<AnnotatorLib::Frame>
AnnotatorLib::Commands::RemoveAnnotationRange::getFrame1() {
  return frame1;
}

shared_ptr<AnnotatorLib::Frame>
AnnotatorLib::Commands::RemoveAnnotationRange::getFrame2() {
  return frame2;
}
