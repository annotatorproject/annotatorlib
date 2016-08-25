#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/RemoveAnnotation.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::RemoveAnnotation::RemoveAnnotation(
    AnnotatorLib::Session *session,
    AnnotatorLib::Annotation *annotation) {
  this->annotation = annotation;
  this->frame = annotation->getFrame();
  this->session = session;
}

bool AnnotatorLib::Commands::RemoveAnnotation::execute() {
  bool success = session->removeAnnotation(annotation);
  if(success) annotation->setVisible(false);
  return success;
}

bool AnnotatorLib::Commands::RemoveAnnotation::undo() {
  annotation->setVisible(true);
  this->session->addAnnotation(this->annotation, this->frame);
  return true;
}

AnnotatorLib::Annotation *
AnnotatorLib::Commands::RemoveAnnotation::getAnnotation() {
  return annotation;
}

