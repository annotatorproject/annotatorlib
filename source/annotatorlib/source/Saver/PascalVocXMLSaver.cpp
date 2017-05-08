// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Saver_PascalVocXMLSaver_BODY

/************************************************************
 XMLSaver class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Saver/PascalVocXMLSaver.h"
#include "AnnotatorLib/Algo/InterpolateAnnotation.h"
#include "AnnotatorLib/Frame.h"
#include "AnnotatorLib/Object.h"
#include "AnnotatorLib/Session.h"

#include <fstream>
#include <memory>
#include <unordered_map>

#include <boost/filesystem.hpp>

#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Text.h>
#include <Poco/XML/XMLWriter.h>

using namespace std;

namespace AnnotatorLib {
namespace Saver {

void PascalVocXMLSaver::saveFrame(const Session *session,
                                  const shared_ptr<Frame> frame) {
  std::string number = std::to_string(frame->getFrameNumber());
  // prepend zeros
  number = std::string(8 - number.length(), '0') + number;

  boost::filesystem::path image_path(
      project->getImageSet()->getImagePath(frame->getFrameNumber()));
  std::string filename =
      path + "/" + image_path.filename().stem().string() + ".xml";

  std::ofstream ostr(filename, std::ios::out);
  Poco::XML::DOMWriter writer;
  writer.setNewLine("\n");
  writer.setOptions(Poco::XML::XMLWriter::PRETTY_PRINT);
  document = new Poco::XML::Document;

  Poco::AutoPtr<Poco::XML::Element> root =
      document->createElement("annotation");

  // folder
  Poco::AutoPtr<Poco::XML::Element> folder = document->createElement("folder");
  if (project) {
    folder->appendChild(
        document->createTextNode(image_path.parent_path().filename().string()));
  } else
    folder->appendChild(document->createTextNode("."));
  root->appendChild(folder);

  // filename
  Poco::AutoPtr<Poco::XML::Element> f = document->createElement("filename");
  if (project) {
    f->appendChild(
        document->createTextNode(image_path.filename().stem().string()));
  } else
    f->appendChild(document->createTextNode(number));
  root->appendChild(f);

  // path
  Poco::AutoPtr<Poco::XML::Element> p = document->createElement("path");
  if (project)
    p->appendChild(document->createTextNode(
        project->getImageSet()->getImagePath(frame->getFrameNumber())));
  else
    p->appendChild(document->createTextNode(path + "/" + number));
  root->appendChild(p);

  // source
  Poco::AutoPtr<Poco::XML::Element> source = document->createElement("source");
  Poco::AutoPtr<Poco::XML::Element> database =
      document->createElement("database");
  database->appendChild(document->createTextNode("Unknown"));
  source->appendChild(database);
  root->appendChild(source);

  // segmented
  Poco::AutoPtr<Poco::XML::Element> segmented =
      document->createElement("segmented");
  segmented->appendChild(document->createTextNode("0"));
  root->appendChild(segmented);

  // object
  for (auto &pair : session->getObjects()) {
    if (session->getAnnotation(frame, pair.second))  // appears in frame?
      root->appendChild(fromObject(session, pair.second, frame));
  }

  document->appendChild(root);

  writer.writeNode(ostr, document);
}

void PascalVocXMLSaver::saveAnnotation(Annotation) {}

void PascalVocXMLSaver::setPath(std::string path) { this->path = path; }

StorageType PascalVocXMLSaver::getType() { return StorageType::PASCALVOCXML; }

void PascalVocXMLSaver::saveSession(const Session *session) {
  for (auto &pair : session->getFrames()) {
    saveFrame(session, pair.second);
  }
}

void PascalVocXMLSaver::saveProject(std::shared_ptr<Project> project) {
  this->project = project;
  saveSession(project->getSession().get());
}

bool PascalVocXMLSaver::close() { return true; }

Poco::AutoPtr<Poco::XML::Element> PascalVocXMLSaver::fromObject(
    const Session *session, const shared_ptr<Object> object,
    const shared_ptr<Frame> frame) {
  Poco::AutoPtr<Poco::XML::Element> element = document->createElement("object");
  // name
  Poco::AutoPtr<Poco::XML::Element> name = document->createElement("name");
  name->appendChild(document->createTextNode(object->getClass()->getName()));
  element->appendChild(name);

  // bndbox
  shared_ptr<Annotation> annotation = session->getAnnotation(frame, object);
  Poco::AutoPtr<Poco::XML::Element> bndbox = document->createElement("bndbox");

  Poco::AutoPtr<Poco::XML::Element> xmin = document->createElement("xmin");
  xmin->appendChild(
      document->createTextNode(std::to_string((int)annotation->getX())));
  Poco::AutoPtr<Poco::XML::Element> ymin = document->createElement("ymin");
  ymin->appendChild(
      document->createTextNode(std::to_string((int)annotation->getY())));
  Poco::AutoPtr<Poco::XML::Element> xmax = document->createElement("xmax");
  xmax->appendChild(document->createTextNode(
      std::to_string((int)(annotation->getX() + annotation->getWidth()))));
  Poco::AutoPtr<Poco::XML::Element> ymax = document->createElement("ymax");
  ymax->appendChild(document->createTextNode(
      std::to_string((int)(annotation->getY() + annotation->getHeight()))));

  bndbox->appendChild(xmin);
  bndbox->appendChild(ymin);
  bndbox->appendChild(xmax);
  bndbox->appendChild(ymax);

  element->appendChild(bndbox);

  // attributes
  for (shared_ptr<Attribute> attribute : annotation->getAttributes()) {
    Poco::AutoPtr<Poco::XML::Element> attrElement =
        document->createElement(attribute->getName());
    attrElement->appendChild(
        document->createTextNode(attribute->getValue()->toString()));
    element->appendChild(attrElement);
  }

  return element;
}

// static attributes (if any)

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of XMLSaver class body
 ************************************************************/
