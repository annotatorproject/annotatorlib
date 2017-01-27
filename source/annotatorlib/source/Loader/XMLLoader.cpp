// Copyright 2016-2017 Annotator Team
#define Annotator_AnnotatorLib_Loader_XMLLoader_BODY

/************************************************************
 XMLLoader class body
 ************************************************************/
// include associated header file
#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Loader/XMLLoader.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

#include <fstream>
#include <memory>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/range/algorithm/remove_if.hpp>

#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/NodeFilter.h>
#include <Poco/DOM/NodeIterator.h>
#include <Poco/DOM/NodeList.h>
#include <Poco/SAX/InputSource.h>

// Derived includes directives

namespace AnnotatorLib {
namespace Loader {

void AnnotatorLib::Loader::XMLLoader::setPath(std::string path) {
  this->path = path;
}

AnnotatorLib::StorageType AnnotatorLib::Loader::XMLLoader::getType() {
  return AnnotatorLib::StorageType::XML;
}

void XMLLoader::loadSession(Session *session) {
  findXMLFiles();

  for (boost::filesystem::path file : xmlFiles) {
    loadFile(file.string(), session);
  }
}

void XMLLoader::findXMLFiles() {
  if (boost::filesystem::exists(this->path)) {
    for (boost::filesystem::directory_iterator it(this->path);
         it != boost::filesystem::directory_iterator(); ++it) {
      if (it->path().extension().string() != ".xml") continue;

      xmlFiles.push_back(*it);
    }
    std::sort(xmlFiles.begin(), xmlFiles.end());
  }
}

void XMLLoader::loadFile(std::string fileName, Session *session) {
  std::ifstream in(fileName);
  Poco::XML::InputSource src(in);

  Poco::XML::DOMParser parser;
  Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&src);
  Poco::AutoPtr<Poco::XML::Element> element = pDoc->getElementById("OBJECTS");

  for (Poco::XML::Node *pNode = element->firstChild(); pNode != 0;
       pNode = pNode->nextSibling()) {
    auto pElem = dynamic_cast<Poco::XML::Element *>(pNode);
    if (pElem) {
      unsigned long id =
          std::stoul(pElem->getElementById("ID", "")->getNodeValue());
      unsigned long start =
          std::stoul(pElem->getElementById("START", "")->getNodeValue());
      unsigned long end =
          std::stoul(pElem->getElementById("END", "")->getNodeValue());
      std::string name = pElem->getElementById("NAME", "")->getNodeValue();
      int ulX = 0;
      int ulY = 0;
      int lrX = 0;
      int lrY = 0;

      parseXY(pElem->getElementById("UL", "")->getNodeValue(), "UL:() ", ulX,
              ulY);
      parseXY(pElem->getElementById("LR", "")->getNodeValue(), "LR:() ", lrX,
              lrY);

      loadAnnotation(id, start, end, name, ulX, ulY, lrX, lrY, session);
    }
  }
}

void XMLLoader::loadAnnotation(unsigned long id, unsigned long start,
                               unsigned long end, std::string name, int ulX,
                               int ulY, int lrX, int lrY, Session *session) {
  int width = lrX - ulX;
  int height = lrY - ulY;
  int x = ulX + width / 2;
  int y = ulY + height / 2;

  shared_ptr<AnnotatorLib::Object> object = session->getObject(id);
  if (!object) {
    object = std::make_shared<Object>(id);
    object->setName(name);
    object->setActive(false);
  }
  shared_ptr<AnnotatorLib::Frame> frame = session->getFrame(start);
  shared_ptr<Annotation> previous = object->getFirstAnnotation();
  if (previous) previous = previous->getLast();

  if (previous && previous->getFrame()->getFrameNumber() == start) {
    return;
  }

  if (frame != nullptr && object != nullptr) {
    shared_ptr<Annotation> annotation = Annotation::make_shared(
        frame, object,
        AnnotationType::RECTANGLE);  // TODO: read type from file!

    annotation->setPosition(x, y, width, height);
    session->addAnnotation(shared_ptr<Annotation>(annotation), true);
  }
}

/**
 * @brief XMLLoader::parseXY
 * @param str The String to parse
 * @param remove Characters having no data
 * @param x
 * @param y
 */
void XMLLoader::parseXY(std::string str, std::string remove, int &x, int &y) {
  try {
    str.erase(boost::remove_if(str, boost::is_any_of(remove)), str.end());

    std::vector<std::string> strs;
    boost::split(strs, str, boost::is_any_of(","));
    x = stoi(strs[0]);
    y = stoi(strs[1]);
  } catch (std::exception &e) {
  }
}

// static attributes (if any)

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of XMLLoader class body
 ************************************************************/
