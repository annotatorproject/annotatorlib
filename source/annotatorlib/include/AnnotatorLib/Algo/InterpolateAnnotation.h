#ifndef ANNOTATOR_ANNOTATORLIB_ALGO_INTERPOLATEANNOTATION_H
#define ANNOTATOR_ANNOTATORLIB_ALGO_INTERPOLATEANNOTATION_H

/************************************************************
 InterpolateAnnotation class header
 ************************************************************/
#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include <memory>
#include <unordered_map>
#include <vector>

using std::shared_ptr;

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
     * @brief Create new annotation with an interpolated position for a given
   * frame.
     * The new annotation will be located between prev and next.
     * This annotations will belong to the same object as prev and next.
     *
     * TODO: If the target frame already contains an annotation of the same
   * object,
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
  static shared_ptr<Annotation> getInterpolation(shared_ptr<Frame> frame,
                                                 shared_ptr<Annotation> start,
                                                 shared_ptr<Annotation> end);

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
  static shared_ptr<Annotation> getInterpolation(
      const std::shared_ptr<Session> session, const shared_ptr<Frame> frame,
      const shared_ptr<Object> object, bool interpolationsOnly = false);

  static std::vector<shared_ptr<Annotation>> getInterpolations(
      const std::shared_ptr<Session> session, shared_ptr<Frame> frame,
      bool interpolationsOnly = false);
};
}
}
#endif
