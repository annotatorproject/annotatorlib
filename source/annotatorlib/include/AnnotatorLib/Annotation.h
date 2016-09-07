#ifndef ANNOTATOR_ANNOTATORLIB_ANNOTATION_H
#define ANNOTATOR_ANNOTATORLIB_ANNOTATION_H

/************************************************************
 Annotation class header
 ************************************************************/
#include <vector>
#include <memory>
#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>

using std::shared_ptr;
using std::weak_ptr;

namespace AnnotatorLib {

class Attribute;
class Frame;
class Object;

/************************************************************/

/**
 * @brief The Annotation class
 * Represents a label for an object on a specific frame.
 */
class ANNOTATORLIB_API Annotation {

 friend class Object;   //an object manages the order of annotations (setNext, setPrevious)
 friend class Session;  //Session needs to register/unregister

 public:
  /////////STATICS/////////////
  static unsigned long genId(const std::shared_ptr<Frame> frame, const std::shared_ptr<Object> obj);

  /**
   * Encapsulates private constructors and registers Annotations to Objects and Frames.
   */
  template<typename... _Args>
  static shared_ptr<Annotation> make_shared(_Args&&... __args) {
    // we need this struct to give std::make_shared(...) access to the private/protected constructors of Annotation
    struct make_shared_enabler : public Annotation {
      make_shared_enabler(_Args &&... args) : Annotation(std::forward<_Args>(args)...) {}
    };
    shared_ptr<Annotation> a = std::make_shared<make_shared_enabler>(std::forward<_Args>(__args)...);
    a->setSelf(a);
    if (!a->isTemporary()) {
        a->setRegistered(true);
    }
    return a;
  }

  /////////CONSTANTS/////////////

  const unsigned long id;
  const shared_ptr<Frame> frame;
  const shared_ptr<Object> object;
  const AnnotationType type;

  /////////////////////////

  virtual ~Annotation() {
    if (registered) {
      setRegistered(false);
    }
  }

  void operator=(const Annotation&) = delete;

  /**
   * @brief operator >: comparing is based on frame-number
   * @param left
   * @param right
   * @return
   */
  bool operator>(const Annotation &right);
  bool operator>=(const Annotation &right);
  bool operator<(const Annotation &right);
  bool operator<=(const Annotation &right);
  bool operator==(const Annotation &right);
  bool operator!=(const Annotation &right);

  ////////METHODS//////////

  unsigned long getId() const;
  const bool is_temporary;

  std::vector<shared_ptr<Attribute>> const& getAttributes() const;
  bool addAttribute(shared_ptr<Attribute> attribute);
  bool removeAttribute(shared_ptr<Attribute> attribute);
  shared_ptr<Frame> getFrame() const;
  shared_ptr<Object> getObject() const;
  AnnotationType getType() const;

  /**
   * @brief setPosition
   * @param x
   * @param y
   */
  void setPosition(float x, float y);

  void setPosition(float x, float y, float width, float height);
  /**
   * @brief setPosition
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

 protected:

  ////////PROTECTED CONSTRUCTORS//////////

  Annotation() = delete;

  Annotation(shared_ptr<Frame> frame,
             shared_ptr<Object> obj,
             AnnotationType type = AnnotationType::RECTANGLE);

  Annotation( shared_ptr<Annotation> a,
              shared_ptr<Frame> f,
              bool isTemporary = false);

  Annotation(unsigned long id,
             const shared_ptr<Frame>& frame,
             const shared_ptr<Object>& obj,
             const AnnotationType type = AnnotationType::RECTANGLE,
             bool isTemporary = false);
  Annotation(const Annotation &obj) = delete;

  ////////////////////////////////////////

  std::vector<shared_ptr<Attribute>> attributes;
  weak_ptr<Annotation> next;
  weak_ptr<Annotation> previous;
  bool registered;

  // top, left corner, width, height
  float x = 0;
  float y = 0;
  float width = 0;
  float height = 0;

  weak_ptr<Annotation> self_;

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

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of Annotation class header
 ************************************************************/

#endif
