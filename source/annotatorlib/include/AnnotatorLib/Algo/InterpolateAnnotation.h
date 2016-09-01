#ifndef ANNOTATOR_ANNOTATORLIB_ALGO_INTERPOLATEANNOTATION_H
#define ANNOTATOR_ANNOTATORLIB_ALGO_INTERPOLATEANNOTATION_H

/************************************************************
 InterpolateAnnotation class header
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

  /**
     * @brief Create new annotation with an interpolated position for a given frame.
     * The new annotation will be located between prev and next.
     * This annotations will belong to the same object as prev and next.
     *
     * TODO: If the target frame already contains an annotation of the same object,
     * we just update the position.
     *
     * Requirements: This frame must be located in between of prev and next.
     * Prev and next must belong to the same Object.
     *
     * @param frame
     * @param start
     * @param end
     * @return
     */
    static AnnotatorLib::Annotation *getInterpolation(Frame *frame, Annotation *start, Annotation *end);

    /**
     * @brief Get interpolation of certain object for certain frame.
     * If object exists already on given frame, the annotation is only
     * updated and returned if interpolationsOnly is not true.
     *
     * @param frame
     * @param object
     * @param interpolationsOnly
     * @return
     */
    static Annotation *getInterpolation(Frame *frame, Object *object, bool interpolationsOnly = false);

    static std::vector<Annotation *> getInterpolations(Frame *frame, const Session *session, bool interpolationsOnly = false);

    static std::vector<Annotation *> getInterpolations(Frame *frame, const std::vector<Object *> objects, bool interpolationsOnly = false);

};

}
}
#endif
