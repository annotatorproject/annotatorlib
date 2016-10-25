// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_ALGO_SMOOTHANNOTATION_H
#define ANNOTATOR_ANNOTATORLIB_ALGO_SMOOTHANNOTATION_H

/************************************************************
 InterpolateAnnotation class header
 ************************************************************/
#include <memory>
#include <unordered_map>
#include <vector>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>

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
class ANNOTATORLIB_API AdjustAnnotation {
 public:
  static shared_ptr<Annotation> getInterpolation(
      const std::shared_ptr<Session> session, const shared_ptr<Frame> frame,
      const shared_ptr<Object> object, unsigned int depth);

  static float interpolate(float p1, float p2, float c2, unsigned int p2depth);
};
}  // Algo
}  // AnnotatorLib
#endif  // ANNOTATOR_ANNOTATORLIB_ALGO_SMOOTHANNOTATION_H
