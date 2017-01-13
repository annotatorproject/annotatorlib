// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Annotation_BODY

/************************************************************
 Annotation class body
 ************************************************************/

#include <assert.h>
#include <algorithm>
#include <cmath>
#include <iostream>
// include associated header file
#include "AnnotatorLib/Annotation.h"
#include "AnnotatorLib/Frame.h"
#include "AnnotatorLib/Object.h"

namespace AnnotatorLib {

////////////////// statics /////////////////////

unsigned long Annotation::genId(const std::shared_ptr<Frame> frame,
                                const std::shared_ptr<Object> obj) {
  // Cantor’s Pairing Function
  return (std::pow(frame->getId(), 2) + 3 * frame->getId() +
          2 * frame->getId() * obj->getId() + obj->getId() +
          std::pow(obj->getId(), 2)) /
         2;
}

//////////////// constructors ///////////////////

Annotation::Annotation(shared_ptr<Frame> frame, shared_ptr<Object> obj,
                       AnnotationType type)
    : Annotation(genId(frame, obj), frame, obj, type) {}

Annotation::Annotation(shared_ptr<Annotation> a, shared_ptr<Frame> frame,
                       bool isInterpolated)
    : Annotation(genId(frame, a->getObject()), frame, a->getObject(),
                 a->getType(), isInterpolated) {
  this->setPosition(a->getX(), a->getY(), a->getWidth(), a->getHeight());
    for(std::shared_ptr<Attribute> attribute: a->getAttributesWithoutDefaults()){
        this->addAttribute(std::make_shared<Attribute>(attribute));
    }
}

Annotation::Annotation(unsigned long id, const shared_ptr<Frame> &frame,
                       const shared_ptr<Object> &obj, const AnnotationType type,
                       bool isInterpolated)
    : id(id),
      frame(frame),
      object(obj),
      type(type),
      is_temporary(isInterpolated) {}

//////////////// public methods ///////////////////

bool Annotation::operator>(const Annotation &right) const {
  return *this->frame > *right.frame;
}

bool Annotation::operator<(const Annotation &right) const {
  return *this->frame < *right.frame;
}

bool Annotation::operator<=(const Annotation &right) const {
  return *this->frame <= *right.frame;
}

bool Annotation::operator>=(const Annotation &right) const {
  return *this->frame >= *right.frame;
}

bool Annotation::operator==(const Annotation &right) const {
  return *this->frame == *right.frame;
}

bool Annotation::operator!=(const Annotation &right) const {
  return *this->frame != *right.frame;
}

unsigned long Annotation::getId() const { return id; }

std::vector<shared_ptr<Attribute>> Annotation::getAttributes() {
  std::vector<shared_ptr<Attribute>> ret;
  ret.insert(ret.end(), attributes.begin(), attributes.end());

  for (shared_ptr<Attribute> att : object->getAttributes()) {
    // skip if default attribute already exists in annotation.
    if (!getAttributeWithoutDefaults(att->getName())) ret.push_back(att);
  }
  return ret;
}

const std::vector<shared_ptr<Attribute>>
    &Annotation::getAttributesWithoutDefaults() const {
  return attributes;
}

bool Annotation::addAttribute(shared_ptr<Attribute> attribute) {
  if (attribute &&
      std::find(attributes.begin(), attributes.end(), attribute) ==
          attributes.end()) {
    attributes.push_back(attribute);
    return true;
  }
  return false;
}

bool Annotation::removeAttribute(shared_ptr<Attribute> attribute) {
  std::vector<shared_ptr<Attribute>>::iterator position =
      std::find(attributes.begin(), attributes.end(), attribute);
  if (position != attributes.end()) {
    attributes.erase(position);
    return true;
  }
  return false;
}

std::shared_ptr<Attribute> Annotation::getAttribute(std::string name) {
  std::shared_ptr<Attribute> ret = getAttributeWithoutDefaults(name);
  if (!ret) ret = object->getAttribute(name);
  return ret;
}

std::shared_ptr<Attribute> Annotation::getAttributeWithoutDefaults(
    std::string name) {
  for (shared_ptr<Attribute> attribute : attributes) {
    if (attribute->getName() == name) return attribute;
  }
  return nullptr;
}

shared_ptr<Frame> Annotation::getFrame() const { return frame; }

shared_ptr<Object> Annotation::getObject() const { return object; }

AnnotationType Annotation::getType() const { return this->type; }

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

float Annotation::getConfidenceScore() { return confidence; }

void Annotation::setConfidenceScore(float conf) {
  assert(conf >= 0.0f);
  assert(conf <= 1.0f);
  confidence = conf;
}

void Annotation::setSelf(weak_ptr<Annotation> self) { this->self_ = self; }

void Annotation::setNext(weak_ptr<Annotation> next) {
  assert(!next.lock() || *this->frame <= *next.lock()->getFrame());
  this->next = next;
}

shared_ptr<Annotation> Annotation::getNext() const {
  if (next.expired()) return shared_ptr<Annotation>(nullptr);
  return next.lock();
}

bool Annotation::hasNext() const {
  return (next.lock().get() != nullptr && next.lock().get() != this);
}

void Annotation::setPrevious(weak_ptr<Annotation> previous) {
  assert(!previous.lock() || *this->frame >= *previous.lock()->getFrame());
  this->previous = previous;
}

shared_ptr<Annotation> Annotation::getPrevious() const {
  if (previous.expired()) return shared_ptr<Annotation>(nullptr);
  return previous.lock();
}

shared_ptr<Annotation> Annotation::getFirst() {
  return object->getFirstAnnotation();
}

shared_ptr<Annotation> Annotation::getLast() {
  return object->getLastAnnotation();
}

bool Annotation::isLast() const {
  return !this->next.lock() || this->next.lock().get() == this;
}

bool Annotation::isFirst() const { return !this->previous.lock(); }

bool Annotation::isTemporary() const { return is_temporary; }

bool Annotation::isRegistered() const { return registered; }

bool Annotation::setRegistered(bool do_register) {
  if (isTemporary()) return false;
  if (do_register && !registered) {
    this->getObject()->addAnnotation(self_);
    this->getFrame()->addAnnotation(self_);
  }
  if (!do_register && registered) {
    this->getObject()->removeAnnotation(frame->getFrameNumber());
    this->getFrame()->removeAnnotation(id);
  }
  registered = do_register;
  return true;
}

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

//////////////// private static methods ///////////////////

void Annotation::registerAnnotation(const shared_ptr<Annotation> a, bool r) {
  a->setRegistered(r);
}

void Annotation::registerAnnotation(const shared_ptr<Annotation> a) {
  a->setRegistered(true);
}

void Annotation::unregisterAnnotation(const shared_ptr<Annotation> a) {
  a->setRegistered(false);
}

}  // End of namespace AnnotatorLib

/************************************************************
 End of Annotation class body
 ************************************************************/
