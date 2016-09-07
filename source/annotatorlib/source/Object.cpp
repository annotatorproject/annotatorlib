// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

#define Annotator_AnnotatorLib_Object_BODY

/************************************************************
 Object class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Object.h"
#include <assert.h>
#include <algorithm>
#include "AnnotatorLib/Annotation.h"
#include "AnnotatorLib/Class.h"

// Derived includes directives

namespace AnnotatorLib {

// statics
static unsigned long lastId = 10000;
static unsigned long lastNamePostfix = 1;

Object::Object() : Object(genId(), shared_ptr<Class>(nullptr)) { name = genName(); }

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

void Object::setName(std::string name) { this->name = name; }

std::string Object::genName() {
  std::string prefix = "unnamed_obj_";
  const shared_ptr<Class> c = getClass();
  if (c) prefix = c->getName() + "_";
  return prefix + std::to_string(lastNamePostfix++);
}

shared_ptr<Class> Object::getClass() const { return objectClass; }

void Object::setClass(shared_ptr<Class> c) { objectClass = c; }

std::vector<shared_ptr<Attribute>> Object::getAttributes() const { return attributes; }

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
  std::vector<shared_ptr<Attribute>>::const_iterator position =
      std::find(attributes.begin(), attributes.end(), attribute);
  if (position != attributes.end()) {
    attributes.erase(position);
    return true;
  }
  return false;
}

shared_ptr<Annotation> Object::getFirstAnnotation() const {
  if (annotations.size() == 0) return nullptr;
  // anntations are sorted by frame-number, thus we directly return the first
  return annotations[0].lock();
}

shared_ptr<Annotation> Object::getLastAnnotation() const {
  if (annotations.size() == 0) return shared_ptr<Annotation>(nullptr);
  // anntations are sorted by frame-number, thus we directly return the last
  return annotations[annotations.size() - 1].lock();
}

std::vector<weak_ptr<Annotation>> const& Object::getAnnotations() const { return annotations; }

bool Object::addAnnotation(shared_ptr<Annotation> annotation) {
    assert(!annotation->isInterpolated());
    return addAnnotationToSortedList(annotation);
}

static struct _CompareAnnotationPointer {
  bool operator()(const weak_ptr<Annotation> left, const shared_ptr<Annotation> right) {
    return *left.lock()->getFrame() < *right->getFrame();
  }
} _CompareAnnotationPointer;

static struct _CompareAnnotationPointerToFrame {
  bool operator()(const weak_ptr<Annotation> left, const Frame right) {
    return *left.lock().get()->getFrame() < right;
  }
} _CompareAnnotationPointerToFrame;

bool Object::removeAnnotation( shared_ptr<Annotation> annotation) {
  // binary search for annotation
  if (annotation && !annotations.empty()) {
    std::vector<weak_ptr<Annotation>>::iterator it =
        std::lower_bound(annotations.begin(), annotations.end(), annotation,
                         _CompareAnnotationPointer);
    if (it != annotations.end() && !it->expired() && annotation == it->lock()) {
      Frame *frame = annotation->getFrame().get();
      if (frame) {
        frame->removeAnnotation(annotation);
      }
      if (annotation->getPrevious())
        annotation->getPrevious()->setNext(annotation->getNext());
      if (annotation->getNext())
        annotation->getNext()->setPrevious(annotation->getPrevious());

      annotation->setNext(weak_ptr<Annotation>());
      annotation->setPrevious(weak_ptr<Annotation>());
      annotations.erase(it);
      return true;
    }
  }
  return false;
}

std::vector<shared_ptr<Frame>> Object::getFrames() const {
  std::vector<shared_ptr<Frame>> frames;
  for (auto& a : annotations) {
    frames.push_back(a.lock()->getFrame());
  }
  return frames;
}

shared_ptr<Annotation> Object::getAnnotation(const Frame *frame) const {
  std::vector<weak_ptr<Annotation>>::const_iterator it =
      std::lower_bound(annotations.begin(), annotations.end(), *frame,
                       _CompareAnnotationPointerToFrame);
  if (it != annotations.cend()) return it->lock();
  return shared_ptr<Annotation>(nullptr);
}

bool Object::appearsInFrame(const Frame *frame) const {
  return getAnnotation(frame) != nullptr;
}

void Object::findClosestKeyFrames(const Frame *target_frame,
                                  shared_ptr<Annotation>& left,
                                  shared_ptr<Annotation>& right) const {
  std::vector<weak_ptr<Annotation>>::const_iterator it =
      std::lower_bound(annotations.cbegin(), annotations.cend(), *target_frame,
                       _CompareAnnotationPointerToFrame);

  std::vector<weak_ptr<Annotation>>::const_iterator it_fwd = it;
  while (it_fwd != annotations.cend() && it_fwd->lock()->isInterpolated()) {
    it_fwd++;
  }
  right = it_fwd->lock();

  while (it != annotations.cbegin()) {
    it--;
    if (!it->lock()->isInterpolated()) break;
  }
  left = it->lock();
  assert(right != left);
  assert(right == nullptr || right->isInterpolated() == false);
  assert(left->isInterpolated() == false);
}

bool Object::addAnnotationToSortedList(weak_ptr<Annotation> a) {
  if (!isActive()) return false;

  // find the position for the lower_bound  element
  std::vector<weak_ptr<Annotation>>::iterator pos = std::lower_bound(
      annotations.begin(), annotations.end(), a.lock(), _CompareAnnotationPointer);

  //is this annotation already in the list?
  if (pos != annotations.end() && a.lock() == pos->lock()) return false;

  // insert it before pos
  std::vector<weak_ptr<Annotation>>::iterator new_pos = annotations.insert(pos, a);

  if (new_pos != annotations.begin()) {
    weak_ptr<Annotation> prev = *std::prev(new_pos);
    prev.lock()->setNext(a);
    a.lock()->setPrevious(prev.lock());
  }

  if (std::next(new_pos) != annotations.end()) {
    weak_ptr<Annotation> next = *std::next(new_pos);
    next.lock()->setPrevious(a.lock());
    a.lock()->setNext(next.lock());
  }

  return true;
}

void Object::setActive(bool is_active) {
  if (is_active) {
    getLastAnnotation()->setNext(weak_ptr<Annotation>());
  } else {
    getLastAnnotation()->setNext(getLastAnnotation()); //points to itself
  }
}

bool Object::isActive() const {
  if (annotations.empty()) return true;
  assert(getLastAnnotation().get() != nullptr);
  return getLastAnnotation()->getNext().get() != getLastAnnotation().get();
}

}  // of namespace AnnotatorLib

/************************************************************
 End of Object class body
 ************************************************************/
