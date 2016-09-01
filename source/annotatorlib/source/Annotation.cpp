// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

#define Annotator_AnnotatorLib_Annotation_BODY

/************************************************************
 Annotation class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Annotation.h"
#include "AnnotatorLib/Frame.h"
#include "AnnotatorLib/Object.h"

#include <assert.h>
#include <algorithm>
// Derived includes directives

namespace AnnotatorLib {

////////////////// statics /////////////////////

static unsigned long lastId = 100000;

unsigned long Annotation::genId() {
  lastId += 5;
  return lastId;
}

//////////////// constructors ///////////////////

Annotation::Annotation(unsigned long id, Frame* frame, Object* obj, AnnotationType type, bool isInterpolated) : id(id), frame(frame), object(obj), type(type), interpolated(isInterpolated)
{
  assert(frame != nullptr);
  assert(obj != nullptr);

  if (lastId < id) lastId = id;  //  avoid collisions when loading annotations from file
  if (!this->isInterpolated())
    registerAnnotation();

}

Annotation::Annotation(Frame* frame, Object* obj, AnnotationType type) : Annotation(genId(), frame, obj, type) { }

Annotation::Annotation(Annotation* a, Frame* frame, bool isInterpolated) : Annotation(genId(), frame, a->getObject(), a->getType(), isInterpolated) {
  this->setPosition(a->getX(), a->getY(), a->getWidth(), a->getHeight());
}

Annotation::Annotation(const Annotation &other) : Annotation(other.getFrame(), other.getObject(), other.getType()) {
  this->attributes = other.attributes;
  this->next = other.next;
  this->previous = other.previous;
  this->x = other.x;
  this->y = other.y;
  this->width = other.width;
  this->height = other.height;
}

Annotation::~Annotation() { }

//////////////// public methods ///////////////////

bool Annotation::operator> (const Annotation & right)
{
  return *this->frame > *right.frame;
}

bool Annotation::operator< (const Annotation & right)
{
  return *this->frame < *right.frame;
}

bool Annotation::operator<= (const Annotation & right)
{
  return *this->frame <= *right.frame;
}

bool Annotation::operator>= (const Annotation & right)
{
  return *this->frame >= *right.frame;
}

bool Annotation::operator== (const Annotation & right)
{
  return *this->frame == *right.frame;
}

bool Annotation::operator!= (const Annotation & right)
{
  return *this->frame != *right.frame;
}

unsigned long Annotation::getId() const { return id; }

std::vector<Attribute *> Annotation::getAttributes() const { return attributes; }

bool Annotation::addAttribute(Attribute *attribute) {
  if (attribute != nullptr &&
      std::find(attributes.begin(), attributes.end(), attribute) ==
          attributes.end()) {
    attributes.push_back(attribute);
    return true;
  }
  return false;
}

bool Annotation::removeAttribute(Attribute *attribute) {
  std::vector<Attribute *>::const_iterator position =
      std::find(attributes.begin(), attributes.end(), attribute);
  if (position != attributes.end()) {
    attributes.erase(position);
    return true;
  }
  return false;
}

Frame *Annotation::getFrame() const { return frame; }

// removed this setter function, since we don't want that the user can change this afterwards
//void Annotation::setFrame(Frame *frame) {
//  if (this->frame != frame) {
//    this->frame = frame;
//    // if(frame != nullptr)
//    //    frame->addAnnotation(this);
//  }
//}

Object *Annotation::getObject() const { return object; }

// removed this setter function, since we don't want that the user can change this afterwards
//void Annotation::setObject(Object *object) {
//  if (this->object != object) {
//    this->object = object;
//    if (object != nullptr) object->addAnnotation(this);
//  }
//}

AnnotationType Annotation::getType() const { return this->type; }

//void Annotation::setType(AnnotationType type) { this->type = type; }

void Annotation::setCenterPosition(float x, float y, float hradius,
                                   float vradius) {
  setX(x);
  setY(y);
  setHRadius(hradius);
  setVRadius(vradius);
}

float Annotation::getX() const { return x; }

void Annotation::setX(float x) { this->x = x; }

float Annotation::getY() const { return y; }

void Annotation::setY(float y) { this->y = y; }

float Annotation::getWidth() const { return width; }

void Annotation::setWidth(float width) {
  assert(width > 0);
  this->width = width;
}

float Annotation::getHeight() const { return height; }

void Annotation::setHeight(float height) {
  assert(height > 0);
  this->height = height;
}

float Annotation::getHRadius() const { return width / 2; }

void Annotation::setHRadius(float hradius) {
  assert(hradius > 0);
  if (hradius < 0) hradius *= -1;
  this->width = hradius * 2;
}

float Annotation::getVRadius() const { return height / 2; }

void Annotation::setVRadius(float vradius) {
  assert(vradius > 0);
  if (vradius < 0) vradius *= -1;
  this->height = vradius * 2;
}

void Annotation::setNext(Annotation *next) {
  assert(next == nullptr || *this->frame <= *next->frame);
  this->next = next;
}

Annotation *Annotation::getNext() const { return next; }

bool Annotation::hasNext() const { return (next != nullptr && next != this); }

void Annotation::setPrevious(Annotation *previous) {
  assert(previous == nullptr || *this->frame >= *previous->frame);
  this->previous = previous;
}

Annotation *Annotation::getPrevious() const { return previous; }

Annotation *Annotation::getFirst() {
  if (this->previous == nullptr) return this;
  return previous->getFirst();
}

Annotation *Annotation::getLast() {
  if (this->isLast()) return this;
  return next->getLast();
}

bool Annotation::isLast() const {
  return this->next == nullptr || this->next == this;
}

bool Annotation::isFirst() const { return this->previous == nullptr; }

void Annotation::setInterpolated(bool interpolated) {
  this->interpolated = interpolated;
  registerAnnotation(!interpolated);
}

bool Annotation::isInterpolated() const { return interpolated; }

void Annotation::setPosition(float x, float y) {
  this->x = x;
  this->y = y;
}

void Annotation::setPosition(float x, float y, float width, float height) {
  setX(x);
  setY(y);
  setWidth(width);
  setHeight(height);
}

//////////////// private methods ///////////////////


void Annotation::registerAnnotation(bool r) {
  if (r)
    registerAnnotation();
  else
    unregisterAnnotation();
}

void Annotation::registerAnnotation() {
  if (object)
    object->addAnnotation(this);
  if (frame)
    frame->addAnnotation(this);
  if(object && frame) is_registered = true;
}

void Annotation::unregisterAnnotation() {
  if (object)
    object->removeAnnotation(this);
  if (frame)
    frame->removeAnnotation(this);
  is_registered = false;
}

}  // of namespace AnnotatorLib

/************************************************************
 End of Annotation class body
 ************************************************************/
