// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

#ifndef ANNOTATOR_ANNOTATORLIB_FRAME_H
#define ANNOTATOR_ANNOTATORLIB_FRAME_H

/************************************************************
 Frame class header
 ************************************************************/
#include <unordered_map>
#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>
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

 friend class Annotation; //private access for register/unregister
 friend class Object;

 public:
  Frame() = delete;
  Frame(unsigned long frame_nmb);
  ~Frame() {}

  bool operator>(const Frame& right) const;
  bool operator>=(const Frame& right) const;
  bool operator<(const Frame& right) const;
  bool operator<=(const Frame& right) const;
  bool operator==(const Frame& right) const;
  bool operator!=(const Frame& right) const;

  std::unordered_map<unsigned long, weak_ptr<Annotation>> const& getAnnotations() const;
  bool hasAnnotations() const;
  bool addAnnotation(const shared_ptr<Annotation> annotation);
  bool addAnnotation(const weak_ptr<Annotation> annotation);

  std::unordered_map<unsigned long, shared_ptr<Attribute>> const& getAttributes() const;
  bool addAttribute(const shared_ptr<Attribute> attr);
  bool removeAttribute(const shared_ptr<Attribute> attr);

  unsigned long getFrameNumber() const;
  unsigned long getId( ) const { return getFrameNumber(); }

  bool equals(Frame* other) const;

 protected:

  bool removeAnnotation(const shared_ptr<Annotation> annotation);
  bool removeAnnotation(const weak_ptr<Annotation> annotation);
  bool removeAnnotation(unsigned int id);

  const unsigned long frame_number;
  std::unordered_map<unsigned long, shared_ptr<Attribute>> attributes;
  std::unordered_map<unsigned long, weak_ptr<Annotation>> annotations;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of Frame class header
 ************************************************************/

#endif
