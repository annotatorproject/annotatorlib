// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_FRAME_H
#define ANNOTATOR_ANNOTATORLIB_FRAME_H

/************************************************************
 Frame class header
 ************************************************************/
#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>
#include "AnnotatorLib/Annotation.h"

namespace AnnotatorLib {

class Annotation;
class Attribute;

/************************************************************/

/**
 * @brief The Frame class
 * Representing a frame in a movie or an image.
 */
class ANNOTATORLIB_API Frame {
  friend class Annotation;  // private access for register/unregister
  friend class Object;

 public:
  Frame() = delete;
  Frame(unsigned long frame_nmb);
  ~Frame();

  bool operator>(const Frame& right) const;
  bool operator>=(const Frame& right) const;
  bool operator<(const Frame& right) const;
  bool operator<=(const Frame& right) const;
  bool operator==(const Frame& right) const;
  bool operator!=(const Frame& right) const;

  std::unordered_map<unsigned long, std::weak_ptr<Annotation>> const&
  getAnnotations() const;
  bool hasAnnotations() const;
  bool addAnnotation(const std::shared_ptr<Annotation> annotation);
  bool addAnnotation(const std::weak_ptr<Annotation> annotation);

  std::unordered_map<unsigned long, std::shared_ptr<Attribute>> const&
  getAttributes() const;
  bool addAttribute(const std::shared_ptr<Attribute> attr);
  bool removeAttribute(const std::shared_ptr<Attribute> attr);
  bool hasAttributes() const;

  unsigned long getFrameNumber() const;
  unsigned long getId() const;

  bool equals(Frame* other) const;

  friend std::ostream& operator<<(std::ostream& stream,
                                  const AnnotatorLib::Frame& f) {
    stream << "Frame: " << f.frame_number << " ";
    return stream;
  }

 protected:
  bool removeAnnotation(const std::shared_ptr<Annotation> annotation);
  bool removeAnnotation(const std::weak_ptr<Annotation> annotation);
  bool removeAnnotation(unsigned int id);

  const unsigned long frame_number;

  std::unordered_map<unsigned long, std::weak_ptr<Annotation>> annotations;
  std::unordered_map<unsigned long, std::shared_ptr<Attribute>> attributes;
};

/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/
typedef std::map<unsigned long, std::shared_ptr<Frame>> FrameMap;

}  // of namespace AnnotatorLib

/************************************************************
 End of Frame class header
 ************************************************************/

#endif
