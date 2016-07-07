#ifndef UPDATEOBJECT_H
#define UPDATEOBJECT_H

#include <AnnotatorLib/Commands/Command.h>

namespace AnnotatorLib {

namespace Commands {

class ANNOTATORLIB_API UpdateObject: public Command
{
public:
    UpdateObject();

    bool execute();

    bool undo();
};

}
}
#endif // UPDATEOBJECT_H
