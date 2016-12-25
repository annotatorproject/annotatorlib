// Copyright 2016 Annotator Team
/************************************************************
 Pkg_AnnotatorLib package header
 ************************************************************/

#include "AnnotatorLib/AnnotatorLibDatastructs.h"

#include <string>

/* Package dependency header include                        */

namespace AnnotatorLib {

std::string AttributeTypeToString(AttributeType type) {
  switch (type) {
    case AttributeType::STRING:
      return "String";
    case AttributeType::BOOLEAN:
      return "Boolean";
    case AttributeType::INTEGER:
      return "Integer";
    case AttributeType::FLOAT:
      return "Float";
    case AttributeType::UNKNOWN:
      return "Unknown";
    default:
      break;
  };
  return "Unknown";
}

AttributeType AttributeTypeFromString(std::string str) {
  if (str == "String") return AttributeType::STRING;
  if (str == "Boolean") return AttributeType::BOOLEAN;
  if (str == "Integer") return AttributeType::INTEGER;
  if (str == "Float") return AttributeType::FLOAT;
  return AttributeType::UNKNOWN;
}

std::string StorageTypeToString(StorageType type) {
  switch (type) {
    case StorageType::XML:
      return "xml";
    case StorageType::MYSQL:
      return "mysql";
    case StorageType::SQLITE:
      return "sqlite";
    case StorageType::JSON:
      return "json";
    case StorageType::UNKNOWN:
      return "unknown";
    default:
      break;
  };
  return "unknown";
}

StorageType StorageTypeFromString(std::string str) {
  if (str == "xml") return StorageType::XML;
  if (str == "mysql") return StorageType::MYSQL;
  if (str == "sqlite") return StorageType::SQLITE;
  if (str == "json") return StorageType::JSON;
  return StorageType::UNKNOWN;
}

/**
  Converts a String to an ImageSetType

 * @brief typeFromString
 * @param str
 * @return
 */
ImageSetType ImageSetTypeFromString(std::string str) {
  if (str == "video") return ImageSetType::VIDEO;
  if (str == "images") return ImageSetType::IMAGEFOLDER;
  if (str == "imageftp") return ImageSetType::IMAGEFTP;
  if (str == "camera") return ImageSetType::CAMERA;
  return ImageSetType::UNKNOWN;
}

/**
  Converts ImageSetType to a String

 * @brief typeToString
 * @param type
 * @return
 */
std::string ImageSetTypeToString(ImageSetType type) {
  switch (type) {
    case ImageSetType::UNKNOWN:
      return "unknown";
    case ImageSetType::CAMERA:
      return "camera";
    case ImageSetType::VIDEO:
      return "video";
  case ImageSetType::IMAGEFOLDER:
    return "images";
  case ImageSetType::IMAGEFTP:
    return "imageftp";
    default:
      break;
  };
  return "unknown";
}

/**
 * @brief AnnotationTypeFromString
 * @param str
 * @return
 */
AnnotationType AnnotationTypeFromString(std::string str) {
  if (str == "ellipse")
    return AnnotationType::ELLIPSE;
  else
    return AnnotationType::RECTANGLE;
}

std::string AnnotationTypeToString(AnnotationType type) {
  switch (type) {
    case AnnotationType::ELLIPSE:
      return "ellipse";
    case AnnotationType::RECTANGLE:
      return "rectangle";
    default:
      return "rectangle";
  };
}

}  // of namespace AnnotatorLib
