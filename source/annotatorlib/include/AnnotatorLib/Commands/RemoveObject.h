#ifndef REMOVEOBJECT
#define REMOVEOBJECT

#include <AnnotatorLib/Commands/Command.h>

namespace AnnotatorLib {

class Session;
class Object;

namespace Commands {

class ANNOTATORLIB_API RemoveObject: public Command
{
public:
    RemoveObject() = delete;
    RemoveObject(Session *, Object *);
    ~RemoveObject() { }

    bool execute();

    bool undo();

protected:
    Object *object = nullptr;
    Session *session = nullptr;
};

}
}
#endif // REMOVEOBJECT

