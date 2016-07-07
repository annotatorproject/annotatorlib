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
    NewObject(std::string name, Session * session);

    bool execute();

    bool undo();

    Object *getObject();

protected:
    std::string name = "";
    Object * object = nullptr;
    Session * session;
};

}
}
#endif // NEWOBJECT_H
