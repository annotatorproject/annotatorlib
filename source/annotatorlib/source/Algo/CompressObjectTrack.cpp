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

std::vector<Annotation*> CompressObjectTrack::compress(Session* session,
                                                       Object* object,
                                                       float max_diff) {
  std::vector<Annotation*> removed_elements;

  if (object->getAnnotations().size() < 3) return removed_elements;

  Annotation* curr = object->getFirstAnnotation()->getNext();  // get second
  while (curr->hasNext()) {
    Annotation* a_new = InterpolateAnnotation::getInterpolation(
        curr->getFrame(), curr->getPrevious(), curr->getNext());

    Annotation* prev = curr;
    curr = curr->getNext();

    // check if the interpolation is close enough to safely remove the
    // annotation
    float dist = std::sqrt(std::pow(a_new->getX() - prev->getX(), 2) +
                           std::pow(a_new->getY() - prev->getY(), 2));
    if (dist < max_diff) {
      Commands::RemoveAnnotation cmd(session, prev);
      cmd.execute();
      removed_elements.push_back(prev);
    }
    delete a_new;
  }
  return removed_elements;
}

}  // of namespace Algo
}  // of namespace AnnotatorLib
