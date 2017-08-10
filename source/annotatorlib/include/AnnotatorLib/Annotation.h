// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_ANNOTATION_H
#define ANNOTATOR_ANNOTATORLIB_ANNOTATION_H

/************************************************************
 Annotation class header
 ************************************************************/
#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>

using std::shared_ptr;
using std::weak_ptr;

namespace AnnotatorLib {

class Attribute;
class Object;
class Frame;

/************************************************************/

/**
 * @brief The Annotation class
 * Represents a label for an object on a specific frame.
 */
class ANNOTATORLIB_API Annotation {
  friend class Object;   // an object manages the order of annotations (setNext,
                         // setPrevious)
  friend class Session;  // Session needs to register/unregister

 public:
  /////////STATICS/////////////
  static unsigned long genId(const std::shared_ptr<AnnotatorLib::Frame> frame,
                             const std::shared_ptr<Object> obj);

  /**
   * Encapsulates private constructors and registers Annotations to Objects and
   * Frames.
   */
  template <typename... _Args>
  static shared_ptr<Annotation> make_shared(_Args &&... __args) {
    // we need this struct to give std::make_shared(...) access to the
    // private/protected constructors of Annotation
    struct make_shared_enabler : public Annotation {
      make_shared_enabler(_Args &&... args)
          : Annotation(std::forward<_Args>(args)...) {}
    };
    shared_ptr<Annotation> a =
        std::make_shared<make_shared_enabler>(std::forward<_Args>(__args)...);
    a->setSelf(a);
    if (!a->isTemporary()) {
      a->setRegistered(true);
    }
    if (a->isTemporary()) a->setConfidenceScore(0.0);
    return a;
  }

  /////////CONSTANTS/////////////

  const unsigned long id;
  const shared_ptr<AnnotatorLib::Frame> frame;
  const shared_ptr<Object> object;
  const AnnotationType type;

  /////////////////////////

  ~Annotation() {
    if (registered) {
      setRegistered(false);
    }
  }

  void operator=(const Annotation &) = delete;

  /**
   * @brief operator >: comparing is based on frame-number
   * @param left
   * @param right
   * @return
   */
  bool operator>(const Annotation &right) const;
  bool operator>=(const Annotation &right) const;
  bool operator<(const Annotation &right) const;
  bool operator<=(const Annotation &right) const;
  bool operator==(const Annotation &right) const;
  bool operator!=(const Annotation &right) const;

  ////////METHODS//////////

  unsigned long getId() const;
  const bool is_temporary;

  /**
   * @brief getAttributes
   * Gets all Attributes, also object defaults
   * @return
   */
  std::vector<shared_ptr<Attribute>> getAttributes();

  /**
   * @brief getAttributesWithoutDefaults
   * @return
   */
  const std::vector<shared_ptr<Attribute>> &getAttributesWithoutDefaults()
      const;

  bool addAttribute(shared_ptr<Attribute> attribute);
  bool removeAttribute(shared_ptr<Attribute> attribute);

  /**
   * @brief getAttribute
   * Get attribute by name.
   * @param name
   * @return nullptr if attribute does not exist.
   */
  std::shared_ptr<Attribute> getAttribute(std::string name);

  /**
   * @brief getAttributeWithoutDefaults
   * Get attribute by name. No default object attributes.
   * @param name
   * @return
   */
  std::shared_ptr<Attribute> getAttributeWithoutDefaults(std::string name);

  shared_ptr<AnnotatorLib::Frame> getFrame() const;
  shared_ptr<Object> getObject() const;

  /**
   * @brief getType
   * Type of Annotation like rect or circle.
   * @return
   */
  AnnotationType getType() const;

  /**
   * @brief setPosition
   * @param x
   * @param y
   */
  void setPosition(float x, float y);

  void setPosition(float x, float y, float width, float height);
  /**
   * @brief setCenterPosition
   * @param x
   * @param y
   * @param hradius the radius horizontally
   * @param vradius the radius vertically
   */
  void setCenterPosition(float x, float y, float hradius, float vradius);

  float getX() const;
  void setX(float x);
  float getY() const;
  void setY(float y);

  float getWidth() const;
  void setWidth(float width);
  float getHeight() const;
  void setHeight(float height);

  float getHRadius() const;
  void setHRadius(float hradius);
  float getVRadius() const;
  void setVRadius(float vradius);

  float getConfidenceScore();
  void setConfidenceScore(float conf);

  shared_ptr<Annotation> getNext() const;
  bool hasNext() const;
  shared_ptr<Annotation> getPrevious() const;

  shared_ptr<Annotation> getFirst();
  shared_ptr<Annotation> getLast();
  bool isLast() const;
  bool isFirst() const;

  bool isTemporary() const;
  bool isRegistered() const;

  bool setRegistered(bool r);

  friend std::ostream &operator<<(std::ostream &stream, const Annotation &a) {
    stream << "Annotation: " << a.getId();
    stream << "; position: " << a.getX() << ", " << a.getY()
           << "; size: " << a.getWidth() << " x " << a.getHeight() << ")"
           << std::endl;
    return stream;
  }

 protected:
  ////////PROTECTED CONSTRUCTORS//////////

  Annotation() = delete;

  Annotation(shared_ptr<AnnotatorLib::Frame> frame, shared_ptr<Object> obj,
             AnnotationType type = AnnotationType::RECTANGLE);

  Annotation(shared_ptr<Annotation> a, shared_ptr<AnnotatorLib::Frame> f,
             bool isTemporary = false);
  Annotation(shared_ptr<Annotation> a, shared_ptr<AnnotatorLib::Object> o,
             bool isTemporary = false);

  Annotation(unsigned long id, const shared_ptr<AnnotatorLib::Frame> &frame,
             const shared_ptr<Object> &obj,
             const AnnotationType type = AnnotationType::RECTANGLE,
             bool isTemporary = false);
  Annotation(const Annotation &obj) = delete;
  // Constructor

  ////////////////////////////////////////

  std::vector<shared_ptr<Attribute>> attributes;
  weak_ptr<Annotation> next;
  weak_ptr<Annotation> previous;
  bool registered = false;

  // top, left corner, width, height
  float x = 0;
  float y = 0;
  float width = 0;
  float height = 0;

  /**
   * @brief confidence
   * a value between 0 and 1.
   * 1 means it was set manually.
   * 0 means it is just interpolated but not accurate.
   * Values in between can be set or used by algorithms.
   */
  float confidence = 0.0f;

  weak_ptr<Annotation> self_;

  std::mutex mtx;

 private:
  /////////////PRIVATE METHODS/////////////

  void setPrevious(weak_ptr<Annotation> previous);
  void setNext(weak_ptr<Annotation> next);
  void setSelf(weak_ptr<Annotation> self);

  /**
   * @brief Register annotation to its object and frame.
   * @param vis
   */
  static void registerAnnotation(const shared_ptr<Annotation> a);
  static void unregisterAnnotation(const shared_ptr<Annotation> a);
  static void registerAnnotation(const shared_ptr<Annotation> a, bool r);
};

/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

typedef std::map<unsigned long, std::shared_ptr<Annotation>> AnnotationMap;

}  // of namespace AnnotatorLib

/************************************************************
 End of Annotation class header
 ************************************************************/

#endif
