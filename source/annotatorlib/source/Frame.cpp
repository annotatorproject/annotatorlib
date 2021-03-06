// Copyright 2016 Annotator Team

#define Annotator_AnnotatorLib_Frame_BODY

/************************************************************
 Frame class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Frame.h"
#include <assert.h>
#include <algorithm>
#include "AnnotatorLib/Attribute.h"

// Derived includes directives

namespace AnnotatorLib {

Frame::Frame(unsigned long frame_number) : frame_number(frame_number) {}

Frame::~Frame() {}

bool Frame::operator>(const Frame &right) const {
  return frame_number > right.frame_number;
}

bool Frame::operator<(const Frame &right) const {
  return frame_number < right.frame_number;
}

bool Frame::operator<=(const Frame &right) const {
  return frame_number <= right.frame_number;
}

bool Frame::operator>=(const Frame &right) const {
  return frame_number >= right.frame_number;
}

bool Frame::operator==(const Frame &right) const {
  return frame_number == right.frame_number;
}

bool Frame::operator!=(const Frame &right) const {
  return frame_number != right.frame_number;
}

std::unordered_map<unsigned long, weak_ptr<Annotation>> const &
Frame::getAnnotations() const {
  return annotations;
}

bool Frame::hasAnnotations() const { return !annotations.empty(); }

bool Frame::addAnnotation(const shared_ptr<Annotation> annotation) {
  if (annotation != nullptr && annotation->getFrame().get() == this) {
    annotations[annotation->getId()] = annotation;
    return true;
  }
  return false;
}

bool Frame::addAnnotation(const weak_ptr<Annotation> annotation) {
  if (!annotation.expired()) {
    annotations[annotation.lock()->getId()] = annotation;
    return true;
  }
  return false;
}

bool Frame::removeAnnotation(const shared_ptr<Annotation> annotation) {
  if (annotation->getFrame().get() == this) return false;
  return removeAnnotation(annotation->getId());
}

bool Frame::removeAnnotation(const weak_ptr<Annotation> annotation) {
  if (annotation.expired()) return false;
  return removeAnnotation(annotation.lock());
}

bool Frame::removeAnnotation(unsigned int id) {
  return annotations.erase(id) > 0;
}

bool Frame::hasAttributes() const { return !attributes.empty(); }

std::unordered_map<unsigned long, shared_ptr<Attribute>> const &
Frame::getAttributes() const {
  return attributes;
}

bool Frame::addAttribute(const shared_ptr<Attribute> attr) {
  return attributes.insert(std::make_pair(attr->getId(), attr)).second;
}

bool Frame::removeAttribute(const shared_ptr<Attribute> attr) {
  return attributes.erase(attr->getId()) > 0;
}

unsigned long Frame::getFrameNumber() const { return frame_number; }

unsigned long Frame::getId() const { return getFrameNumber(); }

bool Frame::equals(Frame *other) const {
  if (this == other) return true;
  if (this->frame_number != other->frame_number) return false;
  if (this->annotations.size() != other->annotations.size()) return false;
  return true;
}

// static attributes (if any)

}  // End of namespace AnnotatorLib

/************************************************************
 End of Frame class body
 ************************************************************/
