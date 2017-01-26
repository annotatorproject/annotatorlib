// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Saver_XMLSaver_BODY

/************************************************************
 XMLSaver class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Saver/XMLSaver.h"
#include "AnnotatorLib/Algo/InterpolateAnnotation.h"
#include "AnnotatorLib/Frame.h"
#include "AnnotatorLib/Object.h"
#include "AnnotatorLib/Session.h"

#include <fstream>
#include <memory>
#include <unordered_map>

#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Text.h>
#include <Poco/XML/XMLWriter.h>

using namespace std;

namespace AnnotatorLib {
namespace Saver {

void XMLSaver::saveFrame(const Session *session,
                         const shared_ptr<Frame> frame) {
  std::string number = std::to_string(frame->getFrameNumber());
  // prepend zeros
  number = std::string(8 - number.length(), '0') + number;

  std::string filename = path + number + ".xml";

  std::ofstream ostr(filename, std::ios::out);
  Poco::XML::DOMWriter writer;
  writer.setNewLine("\n");
  writer.setOptions(Poco::XML::XMLWriter::PRETTY_PRINT);
  document = new Poco::XML::Document;

  Poco::AutoPtr<Poco::XML::Element> root = document->createElement("OBJECTS");
  root->appendChild(meta(frame));
  for (auto &pair : session->getObjects()) {
    if (session->getAnnotation(frame, pair.second))  // appears in frame?
      root->appendChild(fromObject(session, pair.second, frame));
  }

  document->appendChild(root);

  writer.writeNode(ostr, document);
}

void XMLSaver::saveAnnotation(Annotation annotation) {}

void XMLSaver::setPath(std::string path) { this->path = path; }

StorageType XMLSaver::getType() { return StorageType::XML; }

void XMLSaver::saveSession(const Session *session) {
  for (auto &pair : session->getFrames()) {
    saveFrame(session, pair.second);
  }
}

bool XMLSaver::close() { return true; }

Poco::AutoPtr<Poco::XML::Element> XMLSaver::meta(
    const shared_ptr<Frame> frame) {
  Poco::AutoPtr<Poco::XML::Element> element = document->createElement("META");
  Poco::AutoPtr<Poco::XML::Element> filename =
      document->createElement("FILENAME");
  Poco::AutoPtr<Poco::XML::Text> filenameText =
      document->createTextNode(std::to_string(frame->getFrameNumber()));
  filename->appendChild(filenameText);
  element->appendChild(filename);
  return element;
}

Poco::AutoPtr<Poco::XML::Element> XMLSaver::fromObject(
    const Session *session, const shared_ptr<Object> object,
    const shared_ptr<Frame> frame) {
  Poco::AutoPtr<Poco::XML::Element> element = document->createElement("OBJECT");
  // ID
  Poco::AutoPtr<Poco::XML::Element> id = document->createElement("ID");
  id->appendChild(document->createTextNode(std::to_string(object->getId())));
  element->appendChild(id);
  // NAME
  Poco::AutoPtr<Poco::XML::Element> name = document->createElement("NAME");
  name->appendChild(document->createTextNode(object->getName()));
  element->appendChild(name);
  // OBJ_COLOR
  Poco::AutoPtr<Poco::XML::Element> obj_name =
      document->createElement("OBJ_COLOR");
  obj_name->appendChild(document->createTextNode("#0000ff"));
  element->appendChild(obj_name);

  shared_ptr<Annotation> annotation = session->getAnnotation(frame, object);

  element->setAttribute(
      "StartFr",
      std::to_string(
          object->getFirstAnnotation()->getFrame()->getFrameNumber()));
  element->setAttribute(
      "EndFr", std::to_string(
                   object->getLastAnnotation()->getFrame()->getFrameNumber()));

  // START
  Poco::AutoPtr<Poco::XML::Element> start = document->createElement("START");
  // END
  Poco::AutoPtr<Poco::XML::Element> end = document->createElement("END");

  if (annotation->isTemporary()) {
    start->appendChild(document->createTextNode(std::to_string(
        annotation->getPrevious()->getFrame()->getFrameNumber())));
  } else {
    start->appendChild(document->createTextNode(
        std::to_string(annotation->getFrame()->getFrameNumber())));
    end->appendChild(document->createTextNode(
        annotation->getNext()
            ? std::to_string(
                  annotation->getNext()->getFrame()->getFrameNumber())
            : "-1"));
  }

  element->appendChild(start);
  element->appendChild(end);

  // UL
  Poco::AutoPtr<Poco::XML::Element> ul = document->createElement("UL");
  std::string ulStr =
      "UL:(" + std::to_string(annotation->getX() - annotation->getHRadius()) +
      ", " + std::to_string(annotation->getY() - annotation->getHRadius()) +
      ")";
  ul->appendChild(document->createTextNode(ulStr));
  element->appendChild(ul);

  // LR
  Poco::AutoPtr<Poco::XML::Element> lr = document->createElement("LR");
  std::string lrStr =
      "LR:(" + std::to_string(annotation->getX() + annotation->getHRadius()) +
      ", " + std::to_string(annotation->getY() + annotation->getHRadius()) +
      ")";
  lr->appendChild(document->createTextNode(lrStr));
  element->appendChild(lr);

  return element;
}

// static attributes (if any)

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of XMLSaver class body
 ************************************************************/
