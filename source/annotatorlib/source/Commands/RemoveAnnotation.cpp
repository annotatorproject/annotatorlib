// Copyright 2016 Annotator Team
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

bool AnnotatorLib::Commands::RemoveAnnotation::execute(
    AnnotatorLib::Session *informSession) {
  shared_ptr<Annotation> removedAnnotation =
      session->removeAnnotation(annotation->getId());
  bool ret = annotation == removedAnnotation;
  if (informSession) {
    informSession->updateAnnotation(this->annotation);
  }
  return ret;
}

bool AnnotatorLib::Commands::RemoveAnnotation::undo(
    AnnotatorLib::Session *informSession) {
  this->session->addAnnotation(this->annotation);
  if (informSession) {
    informSession->updateAnnotation(this->annotation);
  }
  return true;
}

shared_ptr<AnnotatorLib::Annotation>
AnnotatorLib::Commands::RemoveAnnotation::getAnnotation() {
  return annotation;
}
