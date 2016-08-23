#include <AnnotatorLib/Commands/NewObject.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::NewObject::NewObject(Session *session)
{
    this->session = session;
    this->object = new AnnotatorLib::Object();
}

AnnotatorLib::Commands::NewObject::NewObject(Session *session, unsigned long id)
{
    this->session = session;
    this->object = new AnnotatorLib::Object(id);
}

bool AnnotatorLib::Commands::NewObject::execute()
{

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
