#include <memory>

#include <boost/python.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/raw_function.hpp>

#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Class.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Object.h>

using namespace boost::python;
using namespace AnnotatorLib;

std::shared_ptr<Annotation> createAnnotation(std::shared_ptr<Frame> frame,
                                             std::shared_ptr<Object> obj) {
  return Annotation::make_shared(frame, obj);
}

BOOST_PYTHON_MODULE(pyannotatorlib) {
  /* ANNOTATION */
  class_<Annotation, std::shared_ptr<Annotation>, boost::noncopyable>(
      "Annotation", no_init)
      .def("construct", &createAnnotation)
      .staticmethod("construct")
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

  /* FRAME */
  class_<Frame, std::shared_ptr<Frame>>("Frame", no_init)
      .def(init<unsigned long>())
      .def("get_number", &Frame::getFrameNumber)
      .def("get_id", &Frame::getFrameNumber)
      .def("has_annotations", &Frame::hasAnnotations);

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
};
