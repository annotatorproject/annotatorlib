// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Saver_XMLSaver_BODY

/************************************************************
 XMLSaver class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Saver/XMLSaver.h"
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <memory>
#include <unordered_map>
#include "AnnotatorLib/Algo/InterpolateAnnotation.h"
#include "AnnotatorLib/Frame.h"
#include "AnnotatorLib/Object.h"
#include "AnnotatorLib/Session.h"

using namespace std;

namespace AnnotatorLib {
namespace Saver {

void XMLSaver::saveFrame(const Session *session,
                         const shared_ptr<Frame> frame) {
  QString filename =
      QString::fromStdString(path) +
      QString("%1").arg(frame->getFrameNumber(), 8, 10, QChar('0')) + ".xml";

  QFile file(filename);
  file.open(QIODevice::WriteOnly | QIODevice::Text);

  if (file.isOpen()) {
    QTextStream stream(&file);
    document.clear();
    QDomElement root = document.createElement("OBJECTS");
    root.appendChild(meta(frame));
    for (auto &pair : session->getObjects()) {
      if (session->getAnnotation(frame, pair.second))  // appears in frame?
        root.appendChild(fromObject(session, pair.second, frame));
    }

    document.appendChild(root);
    document.save(stream, QDomNode::EncodingFromTextStream);
    file.close();
  }
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

QDomElement XMLSaver::meta(const shared_ptr<Frame> frame) {
  QDomElement element = document.createElement("META");
  QDomElement filename = document.createElement("FILENAME");
  QDomText filenameText =
      document.createTextNode(QString::number(frame->getFrameNumber()));
  filename.appendChild(filenameText);
  element.appendChild(filename);
  return element;
}

QDomElement XMLSaver::fromObject(const Session *session,
                                 const shared_ptr<Object> object,
                                 const shared_ptr<Frame> frame) {
  QDomElement element = document.createElement("OBJECT");
  // ID
  QDomElement id = document.createElement("ID");
  id.appendChild(document.createTextNode(QString::number(object->getId())));
  element.appendChild(id);
  // NAME
  QDomElement name = document.createElement("NAME");
  name.appendChild(
      document.createTextNode(QString::fromStdString(object->getName())));
  element.appendChild(name);
  // OBJ_COLOR
  QDomElement obj_name = document.createElement("OBJ_COLOR");
  obj_name.appendChild(document.createTextNode("#0000ff"));
  element.appendChild(obj_name);

  shared_ptr<Annotation> annotation = session->getAnnotation(frame, object);

  element.setAttribute(
      "StartFr",
      QString::number(
          object->getFirstAnnotation()->getFrame()->getFrameNumber()));
  element.setAttribute(
      "EndFr", QString::number(
                   object->getLastAnnotation()->getFrame()->getFrameNumber()));

  // START
  QDomElement start = document.createElement("START");
  // END
  QDomElement end = document.createElement("END");

  if (annotation->isTemporary()) {
    start.appendChild(document.createTextNode(QString::number(
        annotation->getPrevious()->getFrame()->getFrameNumber())));
  } else {
    start.appendChild(document.createTextNode(
        QString::number(annotation->getFrame()->getFrameNumber())));
    end.appendChild(document.createTextNode(
        annotation->getNext()
            ? QString::number(
                  annotation->getNext()->getFrame()->getFrameNumber())
            : "-1"));
  }

  element.appendChild(start);
  element.appendChild(end);

  // UL
  QDomElement ul = document.createElement("UL");
  QString ulStr =
      "UL:(" + QString::number(annotation->getX() - annotation->getHRadius()) +
      ", " + QString::number(annotation->getY() - annotation->getHRadius()) +
      ")";
  ul.appendChild(document.createTextNode(ulStr));
  element.appendChild(ul);

  // LR
  QDomElement lr = document.createElement("LR");
  QString lrStr =
      "LR:(" + QString::number(annotation->getX() + annotation->getHRadius()) +
      ", " + QString::number(annotation->getY() + annotation->getHRadius()) +
      ")";
  lr.appendChild(document.createTextNode(lrStr));
  element.appendChild(lr);

  return element;
}

// static attributes (if any)

}  // of namespace Saver
}  // of namespace AnnotatorLib

/************************************************************
 End of XMLSaver class body
 ************************************************************/
