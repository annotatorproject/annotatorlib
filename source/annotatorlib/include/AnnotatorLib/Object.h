// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

#ifndef ANNOTATOR_ANNOTATORLIB_OBJECT_H
#define ANNOTATOR_ANNOTATORLIB_OBJECT_H


/************************************************************
 Object class header
 ************************************************************/

#include <string>
#include <vector>

#include <AnnotatorLib/annotatorlib_api.h>
#include <AnnotatorLib/AnnotatorLibDatastructs.h>

#include "AnnotatorLib/Annotation.h"
#include "AnnotatorLib/Attribute.h"
#include "AnnotatorLib/Frame.h"

namespace AnnotatorLib {

class Class;

/************************************************************/
/**
 * @brief The Object class that represents an object of a specific class.
 */
class ANNOTATORLIB_API Object {
public:

    const unsigned long id = 0;

    Object();
    Object(Class* c);
    Object(unsigned long id);
    Object(unsigned long id, Class* c);

	/**
	 * 
	 * @return id 
	 */
    static unsigned long genId();

    unsigned long getId() const;

    std::string getName();
    void setName(std::string name);

    Class *getClass() const;
    void setClass(Class *c);

    std::vector<Attribute*> getAttributes() const;
    bool addAttribute(Attribute* attribute);
    bool removeAttribute(Attribute* attribute);

    Annotation *getFirstAnnotation() const;
    Annotation *getLastAnnotation() const;
    std::vector<Annotation*> getAnnotations() const;
    bool addAnnotation(Annotation* annotation);
    bool removeAnnotation(Annotation* annotation);
    bool hasAnnotations() const { return !annotations.empty(); }

    /**
     * @brief Get all frames of this object.
     * Attention: Heavy operation!
     * @return
     */
    std::vector<Frame*> getFrames() const;
    //bool addFrame(Frame* frame);
    //bool removeFrame(Frame* frame);
    bool appearsInFrame(const Frame *frame) const;
    Annotation* getAnnotation(const Frame *frame) const;
    void findClosestKeyFrames(const Frame * target_frame, Annotation*& left, Annotation*& right) const;

private:

    std::string genName();
    bool addAnnotationToSortedList(Annotation* a);

    std::string name;

    Class *objectClass = nullptr;
	/**
	 * 
	 */
    std::vector<Attribute*> attributes;
	/**
	 * 
	 */
    std::vector<Annotation*> annotations;
	/**
	 * 
	 */
    //std::vector<Frame*> frames;

};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

} // of namespace AnnotatorLib

/************************************************************
 End of Object class header
 ************************************************************/

#endif
