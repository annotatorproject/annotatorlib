#ifndef REMOVEANNOTATION
#define REMOVEANNOTATION

#include <AnnotatorLib/Commands/Command.h>
#include <memory>

using std::shared_ptr;

namespace AnnotatorLib {

class Session;
class Frame;
class Annotation;

namespace Commands {

class ANNOTATORLIB_API RemoveAnnotation : public Command {
 public:
  RemoveAnnotation(Session *, Annotation *);
  ~RemoveAnnotation() {}

  bool execute();

  bool undo();

  Annotation *getAnnotation();

 protected:
  Session *session = nullptr;
  shared_ptr<Annotation> annotation;
};
}
}
#endif  // REMOVEANNOTATION
