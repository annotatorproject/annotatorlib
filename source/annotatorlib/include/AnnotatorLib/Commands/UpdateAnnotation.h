#ifndef UPDATEANNOTATION_H
#define UPDATEANNOTATION_H

#include <AnnotatorLib/Commands/Command.h>

namespace AnnotatorLib {

class Session;
class Annotation;

namespace Commands {

class ANNOTATORLIB_API UpdateAnnotation : public Command {
 public:
  UpdateAnnotation(shared_ptr<Annotation> annotation, float x, float y, float width,
                   float height);

  ~UpdateAnnotation() {}

  bool execute();

  bool undo();

  shared_ptr<Annotation> getAnnotation();

 protected:
  shared_ptr<Annotation> annotation;
  float x;
  float y;
  float width;
  float height;

  float old_x;
  float old_y;
  float old_width;
  float old_height;
};
}
}
#endif  // UPDATEANNOTATION_H
