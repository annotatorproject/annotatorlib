#ifndef UPDATEOBJECT_H
#define UPDATEOBJECT_H

#include <AnnotatorLib/Commands/Command.h>

namespace AnnotatorLib {

class Session;
class Object;
class Class;

namespace Commands {

class ANNOTATORLIB_API UpdateObject : public Command
{
public:
    UpdateObject() = delete;

    UpdateObject(Object * obj, Class* c);

    ~UpdateObject() { }

    bool execute();

    bool undo();

protected:
    Object* obj = nullptr;
    Class* new_class = nullptr;
    Class* old_class = nullptr;
};

}
}
#endif // UPDATEANNOTATION_H
