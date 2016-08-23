#ifndef NEWOBJECT_H
#define NEWOBJECT_H

#include <string>
#include <AnnotatorLib/Commands/Command.h>

namespace AnnotatorLib {

class Object;
class Session;

namespace Commands {

class ANNOTATORLIB_API NewObject: public Command
{
public:
    NewObject(Session * session);
    NewObject(Session * session, unsigned long id);

    bool execute();

    bool undo();

    Object *getObject();

protected:
    Object * object = nullptr;
    Session * session;
};

}
}
#endif // NEWOBJECT_H
