#include <AnnotatorLib/Commands/UpdateAnnotation.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>


AnnotatorLib::Commands::UpdateAnnotation::UpdateAnnotation(AnnotatorLib::Annotation *annotation, float x, float y, float hradius, float vradius)
{
    this->x = x;
    this->y = y;
    this->hradius = hradius;
    this->vradius = vradius;
    this->annotation = annotation;
}

bool AnnotatorLib::Commands::UpdateAnnotation::execute()
{
    old_x = annotation->getX();
    old_y = annotation->getY();
    old_hradius = annotation->getHRadius();
    old_vradius = annotation->getVRadius();
    annotation->setPosition(x, y, hradius, vradius);
    return true;
}

bool AnnotatorLib::Commands::UpdateAnnotation::undo()
{
    annotation->setPosition(old_x, old_y, old_hradius, old_vradius);
    return true;
}

AnnotatorLib::Annotation *AnnotatorLib::Commands::UpdateAnnotation::getAnnotation()
{
    return annotation;
}



