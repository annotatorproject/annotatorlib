#include <AnnotatorLib/Algo/AdjustAnnotation.h>
#include <AnnotatorLib/Commands/AdjustNeighbors.h>
#include <AnnotatorLib/Commands/NewAnnotation.h>
#include <AnnotatorLib/Commands/UpdateAnnotation.h>
#include <iostream>

AnnotatorLib::Commands::AdjustNeighbors::AdjustNeighbors(
    std::shared_ptr<Session> session, std::shared_ptr<Annotation> annotation,
    unsigned int range) {
  this->session = session;
  this->annotation = annotation;
  this->range = range;
}

bool AnnotatorLib::Commands::AdjustNeighbors::execute() {
  unsigned long aFrameNbr = annotation->getFrame()->getFrameNumber();
  for (unsigned long f = (-(unsigned long)range) + aFrameNbr;
       f <= (unsigned long)range + aFrameNbr; ++f) {
    shared_ptr<Frame> frame = session->getFrame(f);
    if (!frame)
      frame = std::make_shared<Frame>(f);
    std::shared_ptr<AnnotatorLib::Annotation> cAnnotation =
        AnnotatorLib::Algo::AdjustAnnotation::getInterpolation(
            session, frame, annotation->getObject(), range);
    if (cAnnotation) {
      std::shared_ptr<AnnotatorLib::Commands::Command> command;
      if (cAnnotation->isTemporary()) {

        command = std::make_shared<AnnotatorLib::Commands::NewAnnotation>(
            session, annotation->getObject(), frame, cAnnotation->getX(),
            cAnnotation->getY(), cAnnotation->getWidth(),
            cAnnotation->getHeight());
      } else {
        command = std::make_shared<AnnotatorLib::Commands::UpdateAnnotation>(
            cAnnotation, cAnnotation->getX(), cAnnotation->getY(),
            cAnnotation->getWidth(), cAnnotation->getHeight());
      }
      commands.push_front(command);
      command->execute();
    }
  }
  return true;
}

bool AnnotatorLib::Commands::AdjustNeighbors::undo() {
  for (std::shared_ptr<AnnotatorLib::Commands::Command> command : commands) {
    command->undo();
  }
  return true;
}
