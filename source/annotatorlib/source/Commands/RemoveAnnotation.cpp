#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/RemoveAnnotation.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::RemoveAnnotation::RemoveAnnotation(
    AnnotatorLib::Annotation *annotation) {
  this->annotation = annotation;
}

bool AnnotatorLib::Commands::RemoveAnnotation::execute() {
  this->session->removeAnnotation(this->annotation);
  //TODO: request reload of player

  return true;
}

bool AnnotatorLib::Commands::RemoveAnnotation::undo() {
  this->session->addAnnotation(this->annotation);
  return true;
}

AnnotatorLib::Annotation *
AnnotatorLib::Commands::RemoveAnnotation::getAnnotation() {
  return annotation;
}

