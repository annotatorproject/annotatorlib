#define Annotator_AnnotatorLib_Algo_CompressObjectTrack_BODY

/************************************************************
 CompressObjectTrack class body
 ************************************************************/

// include associated header file
#include <math.h>
#include "AnnotatorLib/Algo/CompressObjectTrack.h"
#include "AnnotatorLib/Algo/InterpolateAnnotation.h"
#include "AnnotatorLib/Commands/RemoveAnnotation.h"
#include "AnnotatorLib/Session.h"

namespace AnnotatorLib {
namespace Algo {

void CompressObjectTrack::compress(Session* session, Object *object, float max_diff) {

  if (object->getAnnotations().size() < 3) return;

  Annotation* curr = object->getFirstAnnotation()->getNext();  //get second
  while (curr->hasNext()) {

      Annotation* a_new = InterpolateAnnotation::getInterpolation(curr->getFrame(), curr->getPrevious(), curr->getNext());

      Annotation*  prev = curr;
      curr = curr->getNext();

      //check if the interpolation is close enough to safely remove the annotation
      if ( std::sqrt( std::pow(a_new->getX() - prev->getX(), 2) +  std::pow(a_new->getY() - prev->getY(), 2)) < max_diff) {
        Commands::RemoveAnnotation cmd(session, prev);
        cmd.execute();
      }
      delete a_new;
  }

}

}  // of namespace Algo
}  // of namespace AnnotatorLib
