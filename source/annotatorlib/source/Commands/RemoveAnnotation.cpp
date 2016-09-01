#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/RemoveAnnotation.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::RemoveAnnotation::RemoveAnnotation(
    AnnotatorLib::Session *session, AnnotatorLib::Annotation *annotation) {
  this->annotation = annotation;
  this->frame = annotation->getFrame();
  this->session = session;
}

bool AnnotatorLib::Commands::RemoveAnnotation::execute() {
  bool success = session->removeAnnotation(annotation);
  return success;
}

bool AnnotatorLib::Commands::RemoveAnnotation::undo() {
  this->session->addAnnotation(this->annotation);
  return true;
}

AnnotatorLib::Annotation *
AnnotatorLib::Commands::RemoveAnnotation::getAnnotation() {
  return annotation;
}
