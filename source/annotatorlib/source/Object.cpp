// Copyright 2016-2017 Annotator Team

#define Annotator_AnnotatorLib_Object_BODY

/************************************************************
 Object class body
 ************************************************************/

#include "AnnotatorLib/Object.h"
#include <assert.h>
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include "AnnotatorLib/Annotation.h"
#include "AnnotatorLib/Class.h"

// Derived includes directives

namespace AnnotatorLib {

// statics
static unsigned long lastId = 100;
static unsigned long namePostfixNmb = 0;

Object::Object() : Object(genId(), shared_ptr<Class>(nullptr)) {
  name = genName();
}

Object::Object(const shared_ptr<Class> c) : Object(genId(), c) {}

Object::Object(unsigned long id, const shared_ptr<Class> c) : id(id) {
  objectClass = c;
  name = genName();
  if (lastId < id)
    lastId = id;  // avoid collisions when loading objects from file
}

unsigned long Object::genId() {
  lastId += 3;
  return lastId;
}

unsigned long Object::getId() const { return id; }

std::string Object::getName() const { return name; }

void Object::setName(std::string name) {
  // avoid postfix collisions when setting a name
  std::string name_postfix = name.substr(name.find('_') + 1);
  if (!name_postfix.empty()) {
    unsigned long nmb;
    try {
      nmb = boost::lexical_cast<unsigned long>(name_postfix);
    } catch (boost::bad_lexical_cast &e) {
    }
    namePostfixNmb = std::max(nmb, namePostfixNmb);
  }
  this->name = name;
}

std::string Object::genName() {
  std::string prefix = "unnamed_obj_";
  const shared_ptr<Class> c = getClass();
  if (c) prefix = c->getName() + "_";
  return prefix + std::to_string(++namePostfixNmb);
}

shared_ptr<Class> Object::getClass() const { return objectClass; }

void Object::setClass(shared_ptr<Class> c) { objectClass = c; }

std::vector<shared_ptr<Attribute>> Object::getAttributes() const {
  return attributes;
}

bool Object::addAttribute(shared_ptr<Attribute> attribute) {
  if (attribute != nullptr &&
      std::find(attributes.begin(), attributes.end(), attribute) ==
          attributes.end()) {
    attributes.push_back(attribute);
    return true;
  }
  return false;
}

bool Object::removeAttribute(shared_ptr<Attribute> attribute) {
  std::vector<shared_ptr<Attribute>>::iterator position =
      std::find(attributes.begin(), attributes.end(), attribute);
  if (position != attributes.end()) {
    attributes.erase(position);
    return true;
  }
  return false;
}

shared_ptr<Attribute> Object::getAttribute(std::string name) {
  for (shared_ptr<Attribute> attribute : attributes) {
    if (attribute->getName() == name) return attribute;
  }
  return nullptr;
}

shared_ptr<Annotation> Object::getFirstAnnotation() const {
  if (annotations.size() == 0) return nullptr;
  // anntations are sorted by frame-number, thus we directly return the first
  return annotations.begin()->second.lock();
}

shared_ptr<Annotation> Object::getLastAnnotation() const {
  if (annotations.size() == 0) return shared_ptr<Annotation>(nullptr);
  // anntations are sorted by frame-number, thus we directly return the last
  return std::prev(annotations.end())->second.lock();
}

std::map<unsigned long, weak_ptr<Annotation>> const &Object::getAnnotations()
    const {
  return annotations;
}

bool Object::addAnnotation(shared_ptr<Annotation> annotation) {
  if (!isActive()) return false;
  assert(!annotation->isTemporary());

  std::pair<std::map<unsigned long, weak_ptr<Annotation>>::iterator, bool>
      result = annotations.insert(
          std::make_pair(annotation->getFrame()->getFrameNumber(), annotation));

  if (result.second) {
    if (result.first != annotations.begin() && annotations.size() > 1) {
      shared_ptr<Annotation> prev = std::prev(result.first)->second.lock();
      prev->setNext(annotation);
      annotation->setPrevious(prev);
    }
    if (result.first != std::prev(annotations.end()) &&
        annotations.size() > 1) {
      shared_ptr<Annotation> next = std::next(result.first)->second.lock();
      next->setPrevious(annotation);
      annotation->setNext(next);
    }
  }

  return result.second;
}

bool Object::addAnnotation(weak_ptr<Annotation> annotation) {
  if (!isActive()) return false;
  if (annotation.expired()) return false;
  return addAnnotation(annotation.lock());
}

bool Object::removeAnnotation(unsigned int frame_nmb) {
  auto it = annotations.find(frame_nmb);

  if (it != annotations.end()) {
    if (it != annotations.begin() && it != std::prev(annotations.end())) {
      shared_ptr<Annotation> prev = std::prev(it)->second.lock();
      shared_ptr<Annotation> next = std::next(it)->second.lock();
      prev->setNext(next);
      next->setPrevious(prev);
    } else {
      if (it == annotations.begin() && annotations.size() > 1) {
        shared_ptr<Annotation> next = std::next(it)->second.lock();
        next->setPrevious(weak_ptr<Annotation>());
      }
      if (it == std::prev(annotations.end()) && annotations.size() > 1) {
        shared_ptr<Annotation> prev = std::prev(it)->second.lock();
        prev->setNext(weak_ptr<Annotation>());
      }
    }
    if (!it->second.expired()) {
      it->second.lock()->setNext(shared_ptr<Annotation>(nullptr));
      it->second.lock()->setPrevious(shared_ptr<Annotation>(nullptr));
    }

    return annotations.erase(it)->first;
  }
  return false;
}

bool Object::removeAnnotation(shared_ptr<Annotation> annotation) {
  return removeAnnotation(annotation->getFrame()->getFrameNumber());
}

std::vector<shared_ptr<Frame>> Object::getFrames() const {
  std::vector<shared_ptr<Frame>> frames;
  for (auto &pair : annotations) {
    frames.push_back(pair.second.lock()->getFrame());
  }
  return frames;
}

shared_ptr<Annotation> Object::getAnnotation(shared_ptr<Frame> frame) const {
  return getAnnotation(frame->getFrameNumber());
}

shared_ptr<Annotation> Object::getAnnotation(unsigned long frame) const {
  auto it = annotations.find(frame);
  if (it != annotations.end()) return it->second.lock();
  return shared_ptr<Annotation>(nullptr);
}

bool Object::appearsInFrame(const shared_ptr<Frame> frame) const {
  return getAnnotation(frame) != nullptr;
}

void Object::findClosestKeyFrames(const shared_ptr<Frame> target_frame,
                                  shared_ptr<Annotation> &left,
                                  shared_ptr<Annotation> &right) const {
  std::map<unsigned long, weak_ptr<Annotation>>::const_iterator it =
      annotations.lower_bound(target_frame->getFrameNumber());

  std::map<unsigned long, weak_ptr<Annotation>>::const_iterator it_fwd = it;
  if (it_fwd != annotations.cend()) {
    while (it_fwd != annotations.cend() &&
           it_fwd->second.lock()->isTemporary()) {
      it_fwd++;
    }
    right = it_fwd->second.lock();
  } else {
    right = nullptr;
  }

  if (it != annotations.cend()) {
    while (it != annotations.cbegin()) {
      it--;
      if (!it->second.lock()->isTemporary()) break;
    }
    left = it->second.lock();

  } else {
    left = std::prev(it)->second.lock();
  }
  if (left->getFrame()->getFrameNumber() > target_frame->getFrameNumber())
    left = nullptr;
  assert(right == nullptr || right->isTemporary() == false);
  assert(left == nullptr || left->isTemporary() == false);
}

shared_ptr<Annotation> Object::findClosestRightKeyFrame(
    const unsigned long target_frame) const {
  std::map<unsigned long, weak_ptr<Annotation>>::const_iterator it =
      annotations.lower_bound(target_frame);

  if (it != annotations.cend()) {
    while (it != annotations.cend() && it->second.lock()->isTemporary()) {
      it++;
    }
  } else {
    return nullptr;
  }
  return it->second.lock();
}

shared_ptr<Annotation> Object::findClosestLeftKeyFrame(
    const unsigned long target_frame) const {
  std::map<unsigned long, weak_ptr<Annotation>>::const_iterator it =
      annotations.lower_bound(target_frame);
  if (it != annotations.cend()) {
    while (it != annotations.cbegin()) {
      if (!it->second.lock()->isTemporary() &&
          it->second.lock()->getFrame()->getFrameNumber() <= target_frame)
        return it->second.lock();
      it--;
    }
    if (it == annotations.cbegin() &&
        it->second.lock()->getFrame()->getFrameNumber() <= target_frame)
      return it->second.lock();
  } else {
    return std::prev(it)->second.lock();
  }
  return nullptr;
}

void Object::setActive(bool is_active) {
  if (is_active) {
    getLastAnnotation()->setNext(weak_ptr<Annotation>());
  } else {
    getLastAnnotation()->setNext(getLastAnnotation());  // points to itself
  }
}

bool Object::isActive() const {
  if (annotations.empty()) return true;
  assert(getLastAnnotation().get() != nullptr);
  return getLastAnnotation()->getNext().get() != getLastAnnotation().get();
}

}  // End of namespace AnnotatorLib

/************************************************************
 End of Object class body
 ************************************************************/
