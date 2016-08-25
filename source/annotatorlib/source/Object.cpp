// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

#define Annotator_AnnotatorLib_Object_BODY

/************************************************************
 Object class body
 ************************************************************/

// include associated header file
#include <algorithm>
#include <assert.h>
#include "AnnotatorLib/Object.h"
#include "AnnotatorLib/Annotation.h"

// Derived includes directives

namespace AnnotatorLib {

// static attributes (if any)

static long lastId = 10000;

/**
 *
 * @return id
 */
Object::Object() : id(genId()) { }

Object::Object(unsigned long id) : id(id) { }

unsigned long Object::genId() {
    lastId += 3;
    return lastId;
}

unsigned long Object::getId() const
{
    return id;
}

std::string Object::getName()
{
    return name;
}

void Object::setName(std::string name)
{
    this->name = name;
}

Class *Object::getClass() const
{
    return objectClass;
}

void Object::setClass(Class *c)
{
    this->objectClass = c;
}

std::vector<Attribute *> Object::getAttributes() const
{
    return attributes;
}

bool Object::addAttribute(Attribute *attribute)
{
    if (attribute != nullptr && std::find(attributes.begin(), attributes.end(), attribute) == attributes.end()) {
        attributes.push_back(attribute);
        return true;
    }
    return false;
}

bool Object::removeAttribute(Attribute *attribute)
{
    std::vector<Attribute *>::const_iterator position = std::find(attributes.begin(), attributes.end(), attribute);
    if (position != attributes.end()){
        attributes.erase(position);
        return true;
    }
    return false;
}

Annotation *Object::getFirstAnnotation() const
{
    if(annotations.size() == 0)
        return nullptr;
    return annotations[0]->getFirst();
}

Annotation *Object::getFirstAnnotation(Frame *frame) const
{
    Annotation *annotation = this->getFirstAnnotation();
    while(annotation != nullptr && !annotation->isLast()){

        if(annotation->getFrame()->getFrameNumber() < frame->getFrameNumber()){
            annotation = annotation->getNext();

        } else if (annotation->getFrame()->getFrameNumber() == frame->getFrameNumber()){
            return annotation;

        } else if (annotation->getFrame()->getFrameNumber() > frame->getFrameNumber()){
            if(annotation->isFirst())
                return nullptr;
            else
                return annotation->getPrevious();
        }
    }
    return nullptr;
}

std::vector<Annotation *> Object::getAnnotations() const
{
    return annotations;
}

bool Object::addAnnotation(Annotation *annotation)
{
    if (annotation != nullptr && annotation->getObject() == this && std::find(annotations.begin(), annotations.end(), annotation) == annotations.end()) {
        annotations.push_back(annotation);        
        return true;
    }
    return false;
}

bool Object::removeAnnotation(Annotation *annotation)
{
    std::vector<Annotation *>::const_iterator position = std::find(annotations.cbegin(), annotations.cend(), annotation);
    if (position != annotations.end()){
        Frame* frame = annotation->getFrame();
        if (frame) {
            frame->removeAnnotation(annotation);
            if (!frame->hasAnnotations()) this->removeFrame(frame);
        }
        annotations.erase(position);
        return true;
    }
    return false;
}

void Object::setVisible( bool v)
{
  visible = v;
  for (std::vector<Annotation *>::iterator pos = annotations.begin(); pos != annotations.end(); ++pos) {
    (*pos)->setVisible(v);
  }
}

std::vector<Frame *> Object::getFrames() const
{
    return frames;
}

bool Object::addFrame(Frame *frame)
{
    if (frame != nullptr && std::find(frames.begin(), frames.end(), frame) == frames.end()) {
        frames.push_back(frame);
        return true;
    }
    return false;
}

bool Object::removeFrame(Frame *frame)
{
    std::vector<Frame *>::const_iterator position = std::find(frames.begin(), frames.end(), frame);
    if (position != frames.end()){
        frames.erase(position);
        return true;
    }
    return false;
}

bool Object::appearsInFrame(Frame *frame) const
{
    if(annotations.size() > 0)
    {
        Annotation *annotation = annotations[0];
        Annotation *first = annotation->getFirst();
        assert(first);
        Annotation *last = annotation->getLast();
        assert(last);
        if(first->getFrame()->getFrameNumber() <= frame->getFrameNumber()
                && last->getFrame()->getFrameNumber() >= frame->getFrameNumber())
            return true;
        if(first->getFrame()->getFrameNumber() <= frame->getFrameNumber()
                && !last->isFinished())
            return true;
    }
    return false;
}

} // of namespace AnnotatorLib

/************************************************************
 End of Object class body
 ************************************************************/
