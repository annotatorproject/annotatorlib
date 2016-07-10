#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/UpdateAnnotation.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::UpdateAnnotation::UpdateAnnotation(
    AnnotatorLib::Annotation *annotation, float x, float y, float width,
    float height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->annotation = annotation;
}

bool AnnotatorLib::Commands::UpdateAnnotation::execute() {
  old_x = annotation->getX();
  old_y = annotation->getY();
  old_width = annotation->getWidth();
  old_height = annotation->getHeight();
  annotation->setPosition(x, y, width, height);
  return true;
}

bool AnnotatorLib::Commands::UpdateAnnotation::undo() {
  annotation->setPosition(old_x, old_y, old_width, old_height);
  return true;
}

AnnotatorLib::Annotation *
AnnotatorLib::Commands::UpdateAnnotation::getAnnotation() {
  return annotation;
}
