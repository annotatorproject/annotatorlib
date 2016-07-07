#ifndef UPDATEANNOTATION_H
#define UPDATEANNOTATION_H

#include <AnnotatorLib/Commands/Command.h>

namespace AnnotatorLib {

class Session;
class Annotation;

namespace Commands {

class ANNOTATORLIB_API UpdateAnnotation: public Command
{
public:
    UpdateAnnotation(Annotation * annotation, float x, float y, float hradius, float vradius);

    bool execute();

    bool undo();

    Annotation *getAnnotation();

protected:
    Annotation *annotation = nullptr;
    float x;
    float y;
    float hradius;
    float vradius;

    float old_x;
    float old_y;
    float old_hradius;
    float old_vradius;
};

}
}
#endif // UPDATEANNOTATION_H
