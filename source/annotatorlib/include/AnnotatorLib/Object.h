// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_OBJECT_H
#define ANNOTATOR_ANNOTATORLIB_OBJECT_H

/************************************************************
 Object class header
 ************************************************************/

#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Attribute.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

using std::weak_ptr;
using std::shared_ptr;

namespace AnnotatorLib {

class Class;

/************************************************************/
/**
 * @brief The Object class that represents an object of a specific class.
 */
class ANNOTATORLIB_API Object {
  friend class Annotation;  // private access for register/unregister

 public:
  const unsigned long id = 0;

  /**
   * @return id
   */
  static unsigned long genId();

  Object();
  Object(const shared_ptr<Class> c);
  Object(unsigned long id,
         const shared_ptr<Class> c = shared_ptr<Class>(nullptr));

  ~Object() {}

  unsigned long getId() const;

  std::string getName() const;
  void setName(std::string name);

  shared_ptr<Class> getClass() const;
  void setClass(shared_ptr<Class> c);

  std::vector<shared_ptr<Attribute>> getAttributes() const;
  bool addAttribute(shared_ptr<Attribute> attribute);
  bool removeAttribute(shared_ptr<Attribute> attribute);

  shared_ptr<Annotation> getFirstAnnotation() const;
  shared_ptr<Annotation> getLastAnnotation() const;
  std::map<unsigned long, weak_ptr<Annotation>> const& getAnnotations() const;
  bool addAnnotation(shared_ptr<Annotation> annotation);
  bool removeAnnotation(shared_ptr<Annotation> annotation);
  bool hasAnnotations() const { return !annotations.empty(); }

  /**
   * @brief Get all frames of this object.
   * Attention: Heavy operation!
   * @return
   */
  std::vector<shared_ptr<Frame>> getFrames() const;
  /**
   * This method is deprecated.
   * Use session getAnnoation(frame, object) and check for nullptr.
   * @brief appearsInFrame
   * @param frame
   * @return
   */
  bool appearsInFrame(const shared_ptr<Frame> frame) const;
  /**
   * This method is deprecated.
   * Use session getAnnoation(frame, object) instead.
   * @brief getAnnotation
   * @param frame
   * @return
   */
  shared_ptr<Annotation> getAnnotation(const shared_ptr<Frame> frame) const;
  shared_ptr<Annotation> getAnnotation(unsigned long frame) const;

  /**
   * @brief findClosestKeyFrames
   *
   *
   * @param target_frame
   * @param left
   * @param right
   */
  void findClosestKeyFrames(const shared_ptr<Frame> target_frame,
                            shared_ptr<Annotation>& left,
                            shared_ptr<Annotation>& right) const;

  /**
   * Searches for the next annotation which frameNumber is greater or equal to
   * than the target_frame.
   *
   * @brief findClosestRightKeyFrame
   * @param target_frame
   * @return
   */
  shared_ptr<Annotation> findClosestRightKeyFrame(
      const unsigned long target_frame) const;

  /**
   * Searches for the next annotation which frameNumber is lower or equal to
   * than the target_frame.
   *
   * @brief findClosestLeftKeyFrame
   * @param target_frame
   * @return
   */
  shared_ptr<Annotation> findClosestLeftKeyFrame(
      const unsigned long target_frame) const;

  void setActive(bool active);

  /**
   * @brief isActive
   * Returns if object is active or blocked for new annotations.
   * @return
   */
  bool isActive() const;

  friend std::ostream& operator<<(std::ostream& stream,
                                  const AnnotatorLib::Object& o) {
    stream << "Object: " << o.getId();

    if (o.getClass()) stream << "; " << o.getClass();

    stream << "; number annotations: " << o.getAnnotations().size()
           << std::endl;
    shared_ptr<Annotation> a = o.getFirstAnnotation();
    stream << "List of Annotations: " << std::endl;
    while (a) {
      stream << *a << std::endl;
      if (a->getNext() == a) break;
      a = a->getNext();
    }
    return stream;
  }

 protected:
  std::string genName();
  bool addAnnotation(weak_ptr<Annotation> annotation);
  bool removeAnnotation(unsigned int frame_nmb);

  std::string name;
  shared_ptr<Class> objectClass;
  std::vector<shared_ptr<Attribute>> attributes;
  std::map<unsigned long, weak_ptr<Annotation>> annotations;
};

/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of Object class header
 ************************************************************/

#endif
