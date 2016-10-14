#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/RemoveAnnotation.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::RemoveAnnotation::RemoveAnnotation(
    std::shared_ptr<AnnotatorLib::Session> session,
    shared_ptr<Annotation> annotation) {
  this->annotation = annotation;
  this->session = session;
}

bool AnnotatorLib::Commands::RemoveAnnotation::execute() {
  shared_ptr<Annotation> removedAnnotation =
      session->removeAnnotation(annotation->getId());
  return annotation == removedAnnotation;
}

bool AnnotatorLib::Commands::RemoveAnnotation::undo() {
  this->session->addAnnotation(this->annotation);
  return true;
}

shared_ptr<AnnotatorLib::Annotation>
AnnotatorLib::Commands::RemoveAnnotation::getAnnotation() {
  return annotation;
}
