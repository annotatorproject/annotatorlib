#ifndef NEWANNOTATION_H
#define NEWANNOTATION_H

#include <string>
#include <AnnotatorLib/Commands/Command.h>

namespace AnnotatorLib {

class Object;
class Class;
class Session;
class Annotation;
class Frame;

namespace Commands {

class ANNOTATORLIB_API NewAnnotation: public Command
{
public:
    NewAnnotation() = delete;

    NewAnnotation(unsigned long newObjectId, Class* newObjectClass, Frame *frame, float x, float y, float width, float height, Session *session, bool isFinished);

    NewAnnotation(Object *object, Frame *frame, float x, float y, float width, float height, Session *session, bool isFinished);

    NewAnnotation(Object *object, Frame *frame, float x, float y, float width, float height, Annotation *next,
                  Annotation *previous, Session *session, bool isFinished);

    NewAnnotation(const NewAnnotation& other);

    bool execute();

    bool undo();

    Annotation *getAnnotation();

protected:
    Annotation *annotation = nullptr;
    Annotation *next = nullptr;
    Annotation *previous = nullptr;
    bool createNewObject = false;
    unsigned long newObjectId = 0;
    Class* newObjectClass;
    bool isFinished = false;
    Object *object;
    Frame *frame;
    Session *session;
    float x;
    float y;
    float width;
    float height;
};

}
}
#endif // NEWANNOTATION_H
