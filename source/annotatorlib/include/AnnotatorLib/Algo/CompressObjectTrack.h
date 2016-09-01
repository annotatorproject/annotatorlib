#ifndef ANNOTATOR_ANNOTATORLIB_ALGO_COMPRESSOBJ_H
#define ANNOTATOR_ANNOTATORLIB_ALGO_COMPRESSOBJ_H

/************************************************************
 CompressObjectTrack class header
 ************************************************************/
#include <vector>

#include <AnnotatorLib/annotatorlib_api.h>
#include <AnnotatorLib/AnnotatorLibDatastructs.h>


namespace AnnotatorLib {

class Object;
class Session;

namespace Algo {

/************************************************************/
/**
 * 
 */
class ANNOTATORLIB_API CompressObjectTrack {
public:

  static void compress(Session* session, Object *object, float max_diff = 5);
};

}
}
#endif
