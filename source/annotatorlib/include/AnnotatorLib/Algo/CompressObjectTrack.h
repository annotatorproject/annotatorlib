// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_ALGO_COMPRESSOBJ_H
#define ANNOTATOR_ANNOTATORLIB_ALGO_COMPRESSOBJ_H

/************************************************************
 CompressObjectTrack class header
 ************************************************************/
#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>
#include <memory>
#include <vector>

using std::shared_ptr;

namespace AnnotatorLib {

class Object;
class Annotation;
class Session;

namespace Algo {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API CompressObjectTrack {
 public:
  static std::vector<shared_ptr<Annotation>> compress(
      std::shared_ptr<Session> session, shared_ptr<Object> object,
      float max_diff = 4);
  static std::vector<shared_ptr<Annotation>> compressSession(
      std::shared_ptr<Session> session, float max_diff = 4);
};
}
}
#endif
