#include <AnnotatorLib/Commands/NewObject.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::NewObject::NewObject(std::string name, Session *session)
{
    this->name = name;
    this->session = session;
}

bool AnnotatorLib::Commands::NewObject::execute()
{
    this->object = new AnnotatorLib::Object();
    object->setName(this->name);
    session->addObject(object);
    return true;
}

bool AnnotatorLib::Commands::NewObject::undo()
{
    session->removeObject(object);
    return true;
}

AnnotatorLib::Object *AnnotatorLib::Commands::NewObject::getObject()
{
    return object;
}
