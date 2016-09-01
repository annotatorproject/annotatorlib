#ifndef COMPRESSOBJECT_CMD_H
#define COMPRESSOBJECT_CMD_H

#include <vector>
#include <AnnotatorLib/Commands/Command.h>

namespace AnnotatorLib {

class Session;
class Object;
class Annotation;

namespace Commands {

class ANNOTATORLIB_API CompressObject : public Command
{
public:
    CompressObject() = delete;

    CompressObject(Session * session, Object * obj);

    ~CompressObject() { }

    bool execute();

    bool undo();

protected:
    Object* obj = nullptr;
    Session* session = nullptr;

private:
    std::vector<Annotation*> removed_annotations;
};

}
}
#endif // UPDATEANNOTATION_H
