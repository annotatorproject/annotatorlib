#ifndef ANNOTATOR_ANNOTATORLIB_ALGO_INTERPOLATEANNOTATION_H
#define ANNOTATOR_ANNOTATORLIB_ALGO_INTERPOLATEANNOTATION_H

/************************************************************
 Annotation class header
 ************************************************************/
#include <vector>

#include <AnnotatorLib/annotatorlib_api.h>
#include <AnnotatorLib/AnnotatorLibDatastructs.h>


namespace AnnotatorLib {

class Object;
class Frame;
class Annotation;
class Session;

namespace Algo {

/************************************************************/
/**
 * 
 */
class ANNOTATORLIB_API InterpolateAnnotation {
public:

    static AnnotatorLib::Annotation *getInterpolation(Frame *frame, Annotation *start, Annotation *end);

    static Annotation *getInterpolation(Frame *frame, Object *object, bool interpolationsOnly = false);

    static std::vector<Annotation *> getInterpolations(Frame *frame, Session *session, bool interpolationsOnly = false);

    static std::vector<Annotation *> getInterpolations(Frame *frame, std::vector<Annotation*> annotations, bool interpolationsOnly = false);

};

}
}
#endif
