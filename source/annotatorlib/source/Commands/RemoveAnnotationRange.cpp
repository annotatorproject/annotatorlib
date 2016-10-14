#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/RemoveAnnotation.h>
#include <AnnotatorLib/Commands/RemoveAnnotationRange.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::RemoveAnnotationRange::RemoveAnnotationRange(
    std::shared_ptr<AnnotatorLib::Session> s,
    shared_ptr<AnnotatorLib::Object> o, unsigned long lowerFrameNmb,
    unsigned long upperFrameNmb) {
  this->session = s;
  this->object = o;
  this->frame1 = lowerFrameNmb;
  this->frame2 = upperFrameNmb;
}

AnnotatorLib::Commands::RemoveAnnotationRange::RemoveAnnotationRange(
    std::shared_ptr<AnnotatorLib::Session> s,
    shared_ptr<AnnotatorLib::Object> o, shared_ptr<AnnotatorLib::Frame> f1,
    shared_ptr<AnnotatorLib::Frame> f2) {
  this->session = s;
  this->object = o;
  this->frame1 = f1->getFrameNumber();
  this->frame2 = f2->getFrameNumber();
}

bool AnnotatorLib::Commands::RemoveAnnotationRange::execute() {
  removedAnnotations.clear();

  // TODO:
  //  std::shared_ptr<AnnotatorLib::Annotation> a =
  //  object->findClosestRightKeyFrame(this->frame1);
  //  while(a && a->getFrame()->getFrameNumber() <= frame2) {
  //      removedAnnotations.push_back(session->removeAnnotation(a->getId(),
  //      true));
  //      if (a == a->getNext())
  //        break;
  //      a = a->getNext();
  //  }

  for (unsigned long i = frame1; i < frame2 + 1; ++i) {
    std::shared_ptr<AnnotatorLib::Frame> f = session->getFrame(i);
    if (f) {
      std::shared_ptr<AnnotatorLib::Annotation> a =
          session->getAnnotation(f, object);
      if (a)
        removedAnnotations.push_back(
            session->removeAnnotation(a->getId(), true));
    }
  }

  return true;
}

bool AnnotatorLib::Commands::RemoveAnnotationRange::undo() {
  bool success = true;
  for (std::shared_ptr<AnnotatorLib::Annotation> annotation :
       removedAnnotations) {
    session->addAnnotation(annotation, true);
  }
  return success;
}

shared_ptr<AnnotatorLib::Object>
AnnotatorLib::Commands::RemoveAnnotationRange::getObject() {
  return object;
}

unsigned long AnnotatorLib::Commands::RemoveAnnotationRange::getFrame1() {
  return frame1;
}

unsigned long AnnotatorLib::Commands::RemoveAnnotationRange::getFrame2() {
  return frame2;
}
