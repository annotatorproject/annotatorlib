// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Algo_CompressObjectTrack_BODY

/************************************************************
 CompressObjectTrack class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Algo/CompressObjectTrack.h"
#include <math.h>
#include "AnnotatorLib/Algo/InterpolateAnnotation.h"
#include "AnnotatorLib/Commands/RemoveAnnotation.h"
#include "AnnotatorLib/Session.h"

namespace AnnotatorLib {
namespace Algo {

std::vector<shared_ptr<Annotation>> CompressObjectTrack::compressSession(
    std::shared_ptr<Session> session, float max_diff) {
  std::vector<shared_ptr<Annotation>> removed_elements;
  for (auto it = session->getObjects().begin();
       it != session->getObjects().end(); it++) {
    if (it->second->hasAnnotations()) {
      std::vector<shared_ptr<Annotation>> removed_elements_obj =
          compress(session, it->second, max_diff);
      if (!removed_elements_obj.empty())
        removed_elements.insert(removed_elements.end(),
                                removed_elements_obj.begin(),
                                removed_elements_obj.end());
    }
  }
  return removed_elements;
}

std::vector<shared_ptr<Annotation>> CompressObjectTrack::compress(
    std::shared_ptr<Session> session, shared_ptr<Object> object,
    float max_diff) {
  std::vector<shared_ptr<Annotation>> removed_elements;

  if (object->getAnnotations().size() < 3) return removed_elements;

  shared_ptr<Annotation> curr =
      object->getFirstAnnotation()->getNext();  // get second
  while (curr && curr->hasNext()) {
    shared_ptr<Annotation> a_new = InterpolateAnnotation::getInterpolation(
        curr->getFrame(), curr->getPrevious(), curr->getNext());

    shared_ptr<Annotation> prev = curr;
    curr = curr->getNext();

    // check if the interpolation is close enough to safely remove the
    // annotation
    float dist = std::sqrt(std::pow(a_new->getX() - prev->getX(), 2) +
                           std::pow(a_new->getY() - prev->getY(), 2));
    float dist_size =
        std::sqrt(std::pow(a_new->getWidth() - prev->getWidth(), 2) +
                  std::pow(a_new->getHeight() - prev->getHeight(), 2));
    if (dist < max_diff && dist_size < max_diff) {
      removed_elements.push_back(
          session->removeAnnotation(prev->getId(), true));
    }
    a_new.reset();
  }
  return removed_elements;
}

}  // of namespace Algo
}  // of namespace AnnotatorLib
