// Copyright 2017 Annotator Team
#define PY_ARRAY_UNIQUE_SYMBOL pbcvt_ARRAY_API
#include <memory>

#include <boost/python.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/raw_function.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Class.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/ImageSet/AbstractImageSet.h>
#include <AnnotatorLib/ImageSet/ImageSetFactory.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Project.h>
#include <AnnotatorLib/Session.h>
#include <AnnotatorLib/Storage/AbstractStorage.h>
#include <AnnotatorLib/Storage/StorageFactory.h>

#include "pyboostcvconverter.hpp"

using namespace boost::python;
using namespace AnnotatorLib;

std::shared_ptr<Annotation> createAnnotation(std::shared_ptr<Frame> frame,
                                             std::shared_ptr<Object> obj) {
  return Annotation::make_shared(frame, obj);
}

void loadImageSets(std::string dir) {
  ImageSet::ImageSetFactory::instance()->loadPlugins(dir);
}

void loadStorages(std::string dir) {
  Storage::StorageFactory::instance()->loadPlugins(dir);
}

#if (PY_VERSION_HEX >= 0x03000000)

static void *init_ar() {
#else
static void init_ar() {
#endif
  Py_Initialize();

  import_array();
  return NUMPY_IMPORT_ARRAY_RETVAL;
}

BOOST_PYTHON_MODULE(pyannotatorlib) {
  init_ar();
  to_python_converter<cv::Mat, pbcvt::matToNDArrayBoostConverter>();
  pbcvt::matFromNDArrayBoostConverter();

  /* ANNOTATION */
  class_<Annotation, std::shared_ptr<Annotation>, boost::noncopyable>(
      "Annotation", no_init)
      .def("construct", &createAnnotation)
      .staticmethod("construct")
      .add_property("x", &Annotation::getX, &Annotation::setX)
      .add_property("y", &Annotation::getY, &Annotation::setY)
      .add_property("width", &Annotation::getWidth, &Annotation::setWidth)
      .add_property("height", &Annotation::getHeight, &Annotation::setHeight)
      .def("get_id", &Annotation::getId)
      .def("get_frame", &Annotation::getFrame)
      .def("get_object", &Annotation::getObject)
      .def("get_next", &Annotation::getNext)
      .def("has_next", &Annotation::hasNext)
      .def("get_previous", &Annotation::getPrevious)
      .def("get_first", &Annotation::getFirst)
      .def("get_last", &Annotation::getLast)
      .def("is_first", &Annotation::isFirst)
      .def("is_last", &Annotation::isLast);

  /* CLASS */
  class_<Class, std::shared_ptr<Class>>("Class")
      .def(init<std::string>())
      .def(init<unsigned long, std::string>())
      .def("get_name", &Class::getName)
      .def("get_id", &Class::getId);

  class_<ClassMap>("ClassMap").def(map_indexing_suite<ClassMap>());

  /* FRAME */
  class_<Frame, std::shared_ptr<Frame>>("Frame", no_init)
      .def(init<unsigned long>())
      .def("get_number", &Frame::getFrameNumber)
      .def("get_id", &Frame::getFrameNumber)
      .def("has_annotations", &Frame::hasAnnotations);

  class_<FrameMap>("FrameMap").def(map_indexing_suite<FrameMap>());

  /* OBJECT */
  class_<Object, std::shared_ptr<Object>>("Object")
      .def(init<std::shared_ptr<Class>>())
      .def(init<unsigned long, std::shared_ptr<Class>>())
      .def("get_id", &Object::getId)
      .def("get_name", &Object::getName)
      .def("set_name", &Object::setName)
      .def("get_class", &Object::getClass)
      .def("is_active", &Object::isActive)
      .def("set_active", &Object::setActive);

  /* PROJECT */
  class_<Project, std::shared_ptr<Project>, boost::noncopyable>("Project",
                                                                no_init)
      .def("load_path", &Project::loadPath)
      .staticmethod("load_path")
      .def("save_path", &Project::savePath)
      .staticmethod("save_path")
      .def("get_name", &Project::getName)
      .def("get_session", &Project::getSession)
      .def("get_imageset", &Project::getImageSet)
      .def("get_storage", &Project::getStorage)
      .def("get_path", &Project::getPath)
      .def("get_imageset_path", &Project::getImageSetPath)
      .def("get_duration", &Project::getDuration)
      .def("save", &Project::save);

  /* SESSION */
  std::shared_ptr<Annotation> (Session::*ga)(const shared_ptr<Frame>,
                                             const shared_ptr<Object>) const =
      &Session::getAnnotation;
  std::shared_ptr<Class> (Session::*gc)(std::string) const = &Session::getClass;

  class_<Session, std::shared_ptr<Session>, boost::noncopyable>("Session",
                                                                no_init)
      .def("get_annotations", &Session::getAnnotations)
      .def("get_annotation", ga)
      .def("get_attribute", &Session::getAttribute)
      .def("get_attributes", &Session::getAttributes)
      .def("get_frames", &Session::getFrames)
      .def("get_frame", &Session::getFrame)
      .def("get_objects", &Session::getObjects)
      .def("get_object", &Session::getObject)
      .def("get_classes", &Session::getClasses)
      .def("get_class", gc);

  /* ABSTRACTIMAGESET */
  class_<ImageSet::AbstractImageSet,
         std::shared_ptr<ImageSet::AbstractImageSet>, boost::noncopyable>(
      "AbstractImageSet", no_init)
      .def("get_path", &ImageSet::AbstractImageSet::getPath)
      .def("get_image_path", &ImageSet::AbstractImageSet::getImagePath)
      .def("goto_position", &ImageSet::AbstractImageSet::gotoPosition)
      .def("get_position", &ImageSet::AbstractImageSet::getPosition)
      .def("get_image", &ImageSet::AbstractImageSet::getImage)
      .def("has_next", &ImageSet::AbstractImageSet::hasNext)
      .def("next", &ImageSet::AbstractImageSet::next)
      .def("size", &ImageSet::AbstractImageSet::size)
      .def("get_fps", &ImageSet::AbstractImageSet::getFPS);

  /* ABSTRACTSTORAGE */
  class_<Storage::AbstractStorage, std::shared_ptr<Storage::AbstractStorage>,
         boost::noncopyable>("AbstractStorage", no_init)
      .def("is_open", &Storage::AbstractStorage::isOpen);

  /* --- */
  def("load_imagesets", &loadImageSets);
  def("load_storages", &loadStorages);
};
