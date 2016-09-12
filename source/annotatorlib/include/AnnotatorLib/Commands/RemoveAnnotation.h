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
  RemoveAnnotation(Session * s, shared_ptr<Annotation> a);
  ~RemoveAnnotation() {}

  bool execute();

  bool undo();

  shared_ptr<AnnotatorLib::Annotation> getAnnotation();

 protected:
  Session *session = nullptr;
  shared_ptr<Annotation> annotation;
};
}
}
#endif  // REMOVEANNOTATION
