// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_SESSION_H
#define ANNOTATOR_ANNOTATORLIB_SESSION_H

/************************************************************
 Session class header
 ************************************************************/
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/AnnotatorAlgoInterface.h>
#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Attribute.h>
#include <AnnotatorLib/Class.h>
#include <AnnotatorLib/Commands/Command.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <memory>  //smart pointer
#include <mutex>
#include <unordered_map>
#include <vector>

using std::shared_ptr;
using std::unordered_map;

namespace AnnotatorLib {

/************************************************************/
/**
 * @brief The Session class
 * Contains pointers to all data within a session.
 */
class ANNOTATORLIB_API Session {
 public:
  Session();
  virtual ~Session();

  virtual void clearData();
  virtual void clearAll();

  // Attributes
  virtual AttributeMap getAttributes() const { return attributes; }
  /**
   * @brief Add an attribute to the session.
   * @param c
   * @return
   */
  virtual bool addAttribute(const shared_ptr<Attribute> attribute);
  virtual shared_ptr<Attribute> removeAttribute(Attribute* attribute);
  virtual shared_ptr<Attribute> getAttribute(unsigned long id) const;

  /**
   * @brief updateAttribute
   * Informs the session that internals of the Attribute have changed.
   * @param attribute
   */
  virtual void updateAttribute(shared_ptr<Attribute> /* attribute */) {}

  // Annotations

  virtual AnnotationMap getAnnotations() const { return annotations; }

  /**
   * @brief Will add the given annotation, the associated object
   * and frame to this session. Checks for duplicates.
   * @param annotation
   * @return
   */
  virtual bool addAnnotation(shared_ptr<Annotation> annotation,
                             bool add_associated_objects = true);
  virtual shared_ptr<Annotation> removeAnnotation(unsigned long id,
                                                  bool unregister = true);
  virtual shared_ptr<Annotation> getAnnotation(unsigned long id) const;
  virtual shared_ptr<Annotation> getAnnotation(const shared_ptr<Frame>,
                                               const shared_ptr<Object>) const;
  /**
   * @brief updateAnnotation
   * Informs session that internals of the Annotation have changed.
   * @param annotation
   */
  virtual void updateAnnotation(shared_ptr<Annotation> /* annotation */) {}

  // Classes
  virtual ClassMap getClasses() const { return classes; }

  /**
   * @brief Add a class to the session.
   * @param c
   * @return
   */
  virtual bool addClass(shared_ptr<Class> c);
  virtual shared_ptr<Class> removeClass(Class* c);
  /**
   * Get class by name.
   * complexity: O(1)
   * @brief getClass
   * @param name
   * @return
   */
  virtual shared_ptr<Class> getClass(std::string name) const;
  /**
   * Deprecated! Use getClass(string name) instead!
   * complexity: O(N)
   * @brief Session::getClass
   * @param id
   * @return
   */
  virtual shared_ptr<Class> getClass(unsigned long id) const;

  /**
   * @brief updateClass
   * Informs session that internals of the Class have changed.
   * @param theClass
   */
  virtual void updateClass(shared_ptr<Class> /* theClass */) {}

  // Frames
  virtual FrameMap getFrames() const { return frames; }

  /**
   * @brief getFrames
   * returns frames within range if exists
   * @param first the first frame
   * @param last the last frame
   * @return
   */
  virtual FrameMap getFramesRange(unsigned long first, unsigned long last);

  /**
   * @brief Will add the given frame and all annotations, objects
   * within this frame to this session. Checks for duplicates.
   * @param frame
   * @return
   */
  virtual bool addFrame(shared_ptr<Frame> frame,
                        bool add_associated_objects = true);
  virtual shared_ptr<Frame> removeFrame(unsigned long frame_nmb,
                                        bool remove_annotations = true);
  /**
   * @brief getFrame by given number.
   * If it does not exist we create it.
   * @param number
   * @return The Frame by given Frame Number
   */
  virtual shared_ptr<Frame> getFrame(unsigned long number);

  /**
   * @brief updateFrame
   * Informs session that internals of the Frame have changed.
   * @param frame
   */
  virtual void updateFrame(shared_ptr<Frame> /* frame */) {}

  /**
   * @brief Will add the given object and all associated annotations, plus
   * frames
   * to this session. Checks for duplicates.
   * @param object
   * @return
   */
  virtual bool addObject(shared_ptr<Object> object,
                         bool add_associated_objects = true);
  virtual shared_ptr<Object> removeObject(unsigned long id,
                                          bool remove_annotations = true);
  virtual shared_ptr<Object> getObject(unsigned long id) const;

  /**
   * @brief updateObject
   * Informs session that internals of the Object have changed.
   * @param object
   */
  virtual void updateObject(shared_ptr<Object> /* object */) {}

  virtual ObjectMap getObjects() const { return objects; }

  /**
   * Executes the command and manages all involved memory.
   * @brief execute
   * @param command
   * @return
   */
  virtual shared_ptr<Commands::Command> execute(
      shared_ptr<AnnotatorLib::Commands::Command> command);
  virtual shared_ptr<Commands::Command> redo();
  virtual shared_ptr<Commands::Command> undo();

 private:
  FrameMap frames;
  ObjectMap objects;
  AttributeMap attributes;
  AnnotationMap annotations;
  ClassMap classes;

  unsigned int commandIndex = 0;
  std::mutex mtx;
  std::vector<std::shared_ptr<AnnotatorLib::Commands::Command>> commands;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of Session class header
 ************************************************************/

#endif
