// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Algo_SmoothAnnotation_BODY

/************************************************************
 InterpolateAnnotation class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Algo/AdjustAnnotation.h"
#include "AnnotatorLib/Algo/InterpolateAnnotation.h"
#include "AnnotatorLib/Annotation.h"
#include "AnnotatorLib/Frame.h"
#include "AnnotatorLib/Session.h"

#include <assert.h>
#include <algorithm>

namespace AnnotatorLib {
namespace Algo {

shared_ptr<Annotation> AdjustAnnotation::getInterpolation(
    const std::shared_ptr<Session> session, shared_ptr<Frame> frame,
    shared_ptr<Object> object, unsigned int depth) {
  assert(frame);
  assert(object.get());

  shared_ptr<Annotation> annotation =
      InterpolateAnnotation::getInterpolation(session, frame, object);
  if (!annotation || annotation->getConfidenceScore() == 1.0f)
    return annotation;

  float confidence = 0.5f;  // interpolation cannot be 1.0 but if I use 0.0 then
                            // min() will always be 0.0

  unsigned int counter = 0;
  float posX = 0;
  float posY = 0;
  float posW = 0;
  float posH = 0;

  for (int i = -depth; i <= (int)depth; ++i) {
    shared_ptr<Frame> nframe = session->getFrame(frame->getFrameNumber() + i);
    if (!nframe) nframe = std::make_shared<Frame>(frame->getFrameNumber() + i);
    shared_ptr<Annotation> nAnnotation =
        InterpolateAnnotation::getInterpolation(session, nframe, object);
    if (nAnnotation && !nAnnotation->isTemporary()) {
      confidence = std::min(confidence, nAnnotation->getConfidenceScore());
      posX += interpolate(annotation->getX(), nAnnotation->getX(),
                          nAnnotation->getConfidenceScore(), std::abs(i));
      posY += interpolate(annotation->getY(), nAnnotation->getY(),
                          nAnnotation->getConfidenceScore(), std::abs(i));
      posW += interpolate(annotation->getWidth(), nAnnotation->getWidth(),
                          nAnnotation->getConfidenceScore(), std::abs(i));
      posH += interpolate(annotation->getHeight(), nAnnotation->getHeight(),
                          nAnnotation->getConfidenceScore(), std::abs(i));
      ++counter;
    }
  }

  if (counter == 0) return nullptr;

  annotation->setX(posX / counter);
  annotation->setY(posY / counter);
  annotation->setWidth(posW / counter);
  annotation->setHeight(posH / counter);
  annotation->setConfidenceScore(confidence);
  return annotation;
}

float AdjustAnnotation::interpolate(float p1, float p2, float c2,
                                    unsigned int p2depth) {
  if (p2depth == 0) return p1;
  return p1 + (p2 - p1) * c2 * 1 / (2 * p2depth);
}

}  // of namespace Algo
}  // of namespace AnnotatorLib
