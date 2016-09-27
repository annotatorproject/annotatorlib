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
  removedAnnotations.clear();
  for (unsigned long i = frame1->getFrameNumber();
       i <= frame2->getFrameNumber(); ++i) {
    std::shared_ptr<AnnotatorLib::Frame> frame = session->getFrame(i);
    if (frame) {
      std::shared_ptr<AnnotatorLib::Annotation> annotation = session->getAnnotation(frame, object);
      if (annotation) {
          removedAnnotations.push_back(session->removeAnnotation(annotation->getId(), true));
      }
    }
  }
}

bool AnnotatorLib::Commands::RemoveAnnotationRange::undo() {
  bool success = true;
  for (std::shared_ptr<AnnotatorLib::Annotation> annotation : removedAnnotations) {
      session->addAnnotation(annotation, true);
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
